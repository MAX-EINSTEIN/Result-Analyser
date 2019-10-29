#include "dataanalysisdialog.hpp"
#include "ui_dataanalysisdialog.h"
#include <QComboBox>
#include <QLineEdit>

DataAnalysisDialog::DataAnalysisDialog(QWidget *parent, FieldList fields) :
    QDialog(parent),
    ui(new Ui::DataAnalysisDialog),
    _fields(fields)
{
    ui->setupUi(this);
    setUpExistingFieldsTableWidget();
    setUpNewFieldsTableWidget();
}

DataAnalysisDialog::~DataAnalysisDialog()
{
    delete ui;
}

void DataAnalysisDialog::setUpExistingFieldsTableWidget()
{
    ui->tw_existing_fields->verticalHeader()->hide();
    ui->tw_existing_fields->setRowCount(_fields.size());
    ui->tw_existing_fields->setColumnCount(3);
    for(size_t i=0; i<_fields.size();i++){
        QComboBox * functions = new QComboBox(nullptr);
        functions->addItem("COLOR()");
        functions->addItem("FORMULA()");
        functions->addItem("FORMAT()");
        QLineEdit * value = new QLineEdit(nullptr);
        ui->tw_existing_fields->setItem(i,0,new QTableWidgetItem(_fields.at(i).c_str()));
        ui->tw_existing_fields->setCellWidget(i,1,functions);
        ui->tw_existing_fields->setCellWidget(i,2,value);
    }
    ui->tw_existing_fields->update();
}

void DataAnalysisDialog::setUpNewFieldsTableWidget()
{
    ui->tw_new_fields->verticalHeader()->hide();
    ui->tw_new_fields->setColumnCount(3);
    ui->tw_new_fields->setRowCount(1);
    QLineEdit * field_name = new QLineEdit(nullptr);
    QComboBox * functions = new QComboBox(nullptr);
    functions->addItem("SUM()");
    functions->addItem("PRODUCT()");
    functions->addItem("AVERAGE()");
    QLineEdit * value = new QLineEdit(nullptr);
    ui->tw_new_fields->setCellWidget(0,0,field_name);
    ui->tw_new_fields->setCellWidget(0,1,functions);
    ui->tw_new_fields->setCellWidget(0,2,value);
}

void DataAnalysisDialog::on_b_add_field_clicked()
{
    QLineEdit * field_name = new QLineEdit(nullptr);
    QComboBox * functions = new QComboBox(nullptr);
    functions->addItem("SUM()");
    functions->addItem("PRODUCT()");
    functions->addItem("AVERAGE()");
    QLineEdit * value = new QLineEdit(nullptr);
    int r = ui->tw_new_fields->rowCount();
    ui->tw_new_fields->insertRow(r);
    ui->tw_new_fields->setCellWidget(r,0,field_name);
    ui->tw_new_fields->setCellWidget(r,1,functions);
    ui->tw_new_fields->setCellWidget(r,2,value);
}
