#include "dataanalysisdialog.hpp"
#include "ui_dataanalysisdialog.h"
#include <QHBoxLayout>


DataAnalysisDialog::DataAnalysisDialog(QWidget *parent, FieldList fields) :
    QDialog(parent),
    ui(new Ui::DataAnalysisDialog),
    _fields(fields)
{
    ui->setupUi(this);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setRowCount(_fields.size());
    ui->tableWidget->setColumnCount(2);
    //ui->tableWidget->horizontalHeaderItem(0)->setData(Qt::DisplayRole, "Fields");
    //ui->tableWidget->horizontalHeaderItem(0)->setData(Qt::DisplayRole, "Functions");
    for(size_t i=0; i<_fields.size();i++){
        QComboBox * functions = new QComboBox(this);
        functions->addItem("SUM()");
        functions->addItem("AVERAGE()");
        functions->addItem("MULT()");
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(_fields.at(i).c_str()));
        ui->tableWidget->setCellWidget(i,1,functions);
    }
    ui->tableWidget->update();
}

DataAnalysisDialog::~DataAnalysisDialog()
{
    delete ui;
}
