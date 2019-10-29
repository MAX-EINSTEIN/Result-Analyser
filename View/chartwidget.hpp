#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include "Utils/exceltool.hpp"

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

using Data = QPair<qreal, QString>;
using DataList = QList<Data>;
using DataTable = QList<DataList>;

QT_CHARTS_USE_NAMESPACE

class ChartWidget: public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = 0);
    ~ChartWidget();

private Q_SLOTS:
    void updateUI();

private:
    DataTable populateDataTable(SheetData listOfScoresList);
    void populateAnimationBox();
    void populateLegendBox();
    void connectSignals();
    QChart *createBarChart() const;

private:
    SheetData _listOfScoresList;
    int _scoreMax;
    QList<QChartView *> _charts;
    DataTable _dataTable;

    Ui_ThemeWidgetForm *ui;
};

#endif /* THEMEWIDGET_H */
