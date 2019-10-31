#include "chartwidget.hpp"
#include "ui_chartwidget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QBarCategoryAxis>
#include <QtWidgets/QApplication>
#include <QtCharts/QValueAxis>
#include <cstdlib>

ChartWidget::ChartWidget(QWidget *parent,SheetData listOfScoresList,
                         int scoreMax, QStringList categoryList,
                         SheetRow titleList, QString chartTitle) :
    QWidget(parent),
    _listOfScoresList(listOfScoresList),
    _scoreMax(scoreMax),
    _categoriesList(categoryList),
    _setTitleList(titleList),
    _chartTitle(chartTitle),
    _dataTable(populateDataTable(_listOfScoresList)),
    ui(new Ui_ChartWidgetForm)
{
    ui->setupUi(this);
    populateAnimationBox();
    populateLegendBox();

    //create charts
    QChartView *chartView;

    chartView = new QChartView(createBarChart());
    ui->gridLayout->addWidget(chartView, 1, 0);
    _charts << chartView;

    // Set the colors from the light theme as default ones
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

    // Update the UI
    updateUI();

    // Set defaults
    ui->antialiasCheckBox->setChecked(true);
    for (QChartView *view : _charts) {
        view->chart()->legend()->setAlignment(Qt::AlignRight);
        view->chart()->legend()->show();
    }
}

ChartWidget::~ChartWidget()
{
    delete ui;
}

DataTable ChartWidget::populateDataTable(SheetData listOfScoresList)
{
    DataTable dataTable;

    for(const auto& list:listOfScoresList){
        DataList dataList;
        for(const auto& value:list){
            qreal percent = std::stod(value)/_scoreMax*100.0;
            QString label = value.c_str();
            dataList << Data(percent, label);
        }
        dataTable << dataList;
    }

//    for(size_t i(0); i<listOfScoresList.size();i++){
//        DataList dataList;
//        for(size_t j(0);j<listOfScoresList.at(i).size();j++){
//            auto value = listOfScoresList.at(j).at(i);
//            qreal percent = std::stod(value)/_scoreMax*100.0;
//            QString label = value.c_str();
//            dataList << Data(percent, label);
//        }
//        dataTable << dataList;
//    }

    qDebug("Printing _dataTable");
    for(const auto&list:_dataTable){
        for(const auto&el:list){
            qDebug(QString::number(el.first).toStdString().c_str());
        }
    }

    return dataTable;
}

void ChartWidget::populateAnimationBox()
{
    // add items to animation combobox
    ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);
}

void ChartWidget::populateLegendBox()
{
    // add items to legend combobox
    ui->legendComboBox->addItem("No Legend ", 0);
    ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
}

QChart *ChartWidget::createBarChart() const
{
    QChart *chart = new QChart();
    chart->setTitle(_chartTitle);

    QBarSeries *series = new QBarSeries();
    for (int i(0); i < _dataTable.count(); i++) {
        QBarSet *set = new QBarSet(_setTitleList.at(i).c_str());
        for (const Data &data : _dataTable[i])
            *set << data.first;
//        for(int j(0); j<_dataTable.at(i).count();j++)
//            *set << _dataTable.at(j).at(i).first;
        series->append(set);
    }
    chart->addSeries(series);

    QBarCategoryAxis* axis = new QBarCategoryAxis();
    axis->append(_categoriesList);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->axisY(nullptr)->setMax(100);

    return chart;
}

void ChartWidget::updateUI()
{
    const auto charts = _charts;

    // Update animation options
    QChart::AnimationOptions options(
                ui->animatedComboBox->itemData(ui->animatedComboBox->currentIndex()).toInt());
    if (!_charts.isEmpty() && _charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView : charts)
            chartView->chart()->setAnimationOptions(options);
    }

    // Update legend alignment
    Qt::Alignment alignment(
                ui->legendComboBox->itemData(ui->legendComboBox->currentIndex()).toInt());

    if (!alignment) {
        for (QChartView *chartView : charts)
            chartView->chart()->legend()->hide();
    } else {
        for (QChartView *chartView : charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }

    // Update antialiasing
    bool checked = ui->antialiasCheckBox->isChecked();
    for (QChartView *chart : charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);
}

