/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "chartwidget.hpp"
#include "ui_themewidget.h"

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

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    _listCount(3),
    _valueMax(10),
    _valueCount(7),
    _dataTable(generateRandomData(_listCount, _valueMax, _valueCount)),
    ui(new Ui_ThemeWidgetForm)
{
    ui->setupUi(this);
    populateAnimationBox();
    populateLegendBox();

    //create charts

    QChartView *chartView;

    chartView = new QChartView(createAreaChart());
    ui->gridLayout->addWidget(chartView, 1, 0);
    _charts << chartView;

    //![5]
    chartView = new QChartView(createLineChart());
    ui->gridLayout->addWidget(chartView, 1, 2);
    //![5]
    _charts << chartView;

    chartView = new QChartView(createBarChart(_valueCount));
    ui->gridLayout->addWidget(chartView, 2, 0);
    _charts << chartView;

    // Set defaults
    ui->antialiasCheckBox->setChecked(true);

    // Set the colors from the light theme as default ones
    QPalette pal = qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xf0f0f0));
    pal.setColor(QPalette::WindowText, QRgb(0x404044));
    qApp->setPalette(pal);

    updateUI();
}

ChartWidget::~ChartWidget()
{
    delete ui;
}

DataTable ChartWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{
    DataTable dataTable;


    // generate random data
        for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) {
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / static_cast<qreal>(valueCount) );
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * (static_cast<qreal>(_valueMax) / static_cast<qreal>( valueCount)),yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            /*
            qDebug(label.toStdString().c_str());
            qDebug(QString::number(value.x()).toStdString().c_str() );
            qDebug(QString::number(yValue).toStdString().c_str());
            qDebug(" ");
            */
            dataList << Data(value, label);
        }
        //qDebug("\n\n");
        dataTable << dataList;
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

QChart *ChartWidget::createAreaChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Area chart");

    // The lower series initialized to zero values
    QLineSeries *lowerSeries = nullptr;
    QString name("Series ");
    int nameIndex = 0;
    for (int i(0); i < _dataTable.count(); i++) {
        QLineSeries *upperSeries = new QLineSeries(chart);
        for (int j(0); j < _dataTable[i].count(); j++) {
            Data data = _dataTable[i].at(j);
            if (lowerSeries) {
                const QVector<QPointF>& points = lowerSeries->pointsVector();
                upperSeries->append(QPointF(j, points[i].y() + data.first.y()));
            } else {
                upperSeries->append(QPointF(j, data.first.y()));
            }
        }
        QAreaSeries *area = new QAreaSeries(upperSeries, lowerSeries);
        area->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(area);
        lowerSeries = upperSeries;
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, _valueCount - 1);
    chart->axes(Qt::Vertical).first()->setRange(0, _valueMax);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ChartWidget::createBarChart(int valueCount) const
{
    Q_UNUSED(valueCount)
    QChart *chart = new QChart();
    chart->setTitle("Bar chart");

    QStackedBarSeries *series = new QStackedBarSeries(chart);
    for (int i(0); i < _dataTable.count(); i++) {
        QBarSet *set = new QBarSet("Bar set " + QString::number(i));
        for (const Data &data : _dataTable[i])
            *set << data.first.y();
        series->append(set);
    }
    chart->addSeries(series);

    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(0, _valueMax * 2);
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");

    return chart;
}

QChart *ChartWidget::createLineChart() const
{
    //![1]
    QChart *chart = new QChart();
    chart->setTitle("Line chart");
    //![1]

    //![2]
    QString name("Series ");
    int nameIndex = 0;
    for (const DataList &list : _dataTable) {
        QLineSeries *series = new QLineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }
    //![2]

    //![3]
    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, _valueMax);
    chart->axes(Qt::Vertical).first()->setRange(0, _valueCount);
    //![3]
    //![4]
    // Add space to label to add space between labels and axis
    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");
    //![4]

    return chart;
}

void ChartWidget::updateUI()
{
    const auto charts = _charts;

    // Update animation options
    //![9]
    QChart::AnimationOptions options(
                ui->animatedComboBox->itemData(ui->animatedComboBox->currentIndex()).toInt());
    if (!_charts.isEmpty() && _charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView : charts)
            chartView->chart()->setAnimationOptions(options);
    }
    //![9]

    // Update legend alignment
    //![10]
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
    //![10]

    // Update antialiasing
    //![11]
    bool checked = ui->antialiasCheckBox->isChecked();
    for (QChartView *chart : charts)
        chart->setRenderHint(QPainter::Antialiasing, checked);
    //![11]
}

