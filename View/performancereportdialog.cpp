#include "performancereportdialog.hpp"
#include "ui_performancereportdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <algorithm>
#include <cstdlib>

PerformanceReportDialog::PerformanceReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PerformanceReportDialog)
{
    ui->setupUi(this);
}

PerformanceReportDialog::~PerformanceReportDialog()
{
    delete ui;
}

void PerformanceReportDialog::on_pb_add_file_clicked()
{
    // Prompt for choosing an excel file
    // [Only excel files from MS excel 2007 onwards are supported]
    QString filename = QFileDialog::getOpenFileName(this,"Choose an excel document",QDir::homePath(),"Excel Files(*.xlsx)");
    auto file = filename.toStdString();
    qDebug(file.c_str());
    auto fields = ExcelTool::readHeaders(file);
    auto stringify = [&fields]()->QString{
            QString string = "";
            for(size_t i=0;i<fields.size();i++){
                string += fields.at(i).c_str();
                if(i!=fields.size()-1) string+=" , ";
            }
            return string;
    };
    int r = ui->tw_file_info->rowCount();
    ui->tw_file_info->insertRow(r);
    QLineEdit* fileLabel = new QLineEdit(filename,nullptr);
    QLineEdit* fieldTitles = new QLineEdit(stringify(), nullptr);
    QLineEdit * fileCategory = new QLineEdit(nullptr);
    ui->tw_file_info->setColumnCount(3);
    ui->tw_file_info->setCellWidget(r,0,fileLabel);
    ui->tw_file_info->setCellWidget(r,1,fieldTitles);
    ui->tw_file_info->setCellWidget(r,2,fileCategory);
    ui->tw_file_info->setHorizontalHeaderLabels({"Files", "Subjects", "Title"});
}

void PerformanceReportDialog::on_buttonBox_accepted()
{
    emit onOkayClicked();
}

int PerformanceReportDialog::scoreMax()
{
    _scoreMax = ui->le_max_score->text().toInt();
    qDebug("Max Score : %d\n", _scoreMax);
    return _scoreMax;
}

QStringList PerformanceReportDialog::fileList()
{
    _fileList.clear();
    for(int i(0);i<ui->tw_file_info->rowCount();i++){
        QLineEdit * fileTitle = qobject_cast<QLineEdit*>(ui->tw_file_info->cellWidget(i,2));
        _fileList << fileTitle->text();
        qDebug(fileTitle->text().toStdString().c_str());
    }
    return _fileList;
}

SheetRow PerformanceReportDialog::subjectList()
{
    QStringList subjectList;
    subjectList.clear();
    for(int i(0);i<ui->tw_file_info->rowCount();i++){
        QLineEdit * fields = qobject_cast<QLineEdit*>(ui->tw_file_info->cellWidget(i,1));
        subjectList << fields->text();
    }
    QStringList allSubjects = subjectList.at(0).split(" , ");
    _subjectList = {};
    for(auto & sub:allSubjects){
        _subjectList.push_back(sub.trimmed().toStdString());
        qDebug(sub.trimmed().toStdString().c_str());
    }
    return _subjectList;
}

SheetData PerformanceReportDialog::listOfScoresList()
{
    QStringList files{};
    for(int i(0);i<ui->tw_file_info->rowCount();i++){
        QLineEdit * file = qobject_cast<QLineEdit*>(ui->tw_file_info->cellWidget(i,0));
        files << file->text();
        qDebug(file->text().toStdString().c_str());
    }
    SheetRow subjects = this->subjectList();
    _listOfScoresList = {};
    SheetRow listOfScores;
    for(const auto &file:files){
        SheetData data = ExcelTool::read(file.toStdString());
        listOfScores = {};
        for(const auto& sub:subjects){
            auto itr = std::find(data.at(0).begin(),data.at(0).end(),sub);
            if(itr!=data.at(0).end()){
                auto index = std::distance(data.at(0).begin(), itr);
                double sum = 0;
                for(size_t i(1);i<data.size();i++){
                    sum += std::stod(data.at(i).at(index));
                }
                double avgScore = sum/(data.size()-1);
                listOfScores.push_back(QString::number(avgScore).toStdString());
            }
        }
        _listOfScoresList.push_back(listOfScores);
    }
    SheetData transpose(_listOfScoresList[0].size(), SheetRow(_listOfScoresList.size(), std::string()));
    for(size_t i(0); i<_listOfScoresList.size();i++){
        for(size_t j(0);j<_listOfScoresList[i].size();j++){
            transpose[j][i] = _listOfScoresList[i][j];
        }
    }
    qDebug("Printing _listOfScoresList");
    for(auto list:_listOfScoresList){
        for(auto el:list){
            qDebug(el.c_str());
        }
    }
    qDebug("Printing transpose");
    for(auto list:transpose){
        for(auto el:list){
            qDebug(el.c_str());
        }
    }
    return transpose;
}
