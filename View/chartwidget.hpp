#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_ThemeWidgetForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

using Data = QPair<QPointF, QString>;
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
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    DataTable populateDataTable();
    void populateAnimationBox();
    void populateLegendBox();
    void connectSignals();
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
    QChart *createLineChart() const;

private:
    int _listCount;
    int _valueMax;
    int _valueCount;
    QList<QChartView *> _charts;
    DataTable _dataTable;

    Ui_ThemeWidgetForm *ui;
};

#endif /* THEMEWIDGET_H */
