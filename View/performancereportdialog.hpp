#ifndef PERFORMANCEREPORTDIALOG_HPP
#define PERFORMANCEREPORTDIALOG_HPP

#include <QDialog>
#include <QStringList>
#include <vector>
#include <string>
#include "Utils/exceltool.hpp"

namespace Ui {
class PerformanceReportDialog;
}

class PerformanceReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PerformanceReportDialog(QWidget *parent = nullptr);
    ~PerformanceReportDialog();

    SheetData listOfScoresList();
    SheetRow subjectList();
    QStringList fileList();
    int scoreMax();

signals:
    void onOkayClicked();

private slots:
    void on_pb_add_file_clicked();

    void on_buttonBox_accepted();

private:
    SheetData _listOfScoresList;
    SheetRow _subjectList;
    QStringList _fileList;
    int _scoreMax;
    Ui::PerformanceReportDialog *ui;
};

#endif // PERFORMANCEREPORTDIALOG_HPP
