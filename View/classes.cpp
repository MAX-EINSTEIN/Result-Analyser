#include "View\classes.hpp"
#include "ui_classes.h"
#include <string>

Classes::Classes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Classes)
{
    ui->setupUi(this);

    ui->lw_list_Classes->addItem("Nursery");
    ui->lw_list_Classes->addItem("L.K.G.");
    ui->lw_list_Classes->addItem("U.K.G.");

    for(int i=1;i<=12;i++)
    ui->lw_list_Classes->addItem("Class "+ QString::number(i));

}

void Classes::setSections(int sections)
{
    _sections = sections;
    std::string Section = "Section ";
    for(int i=0;i < _sections;i++)
    ui->lw_list_Sections->addItem((Section + static_cast<char>(65+i)).c_str());
}


Classes::~Classes()
{
    delete ui;
}
