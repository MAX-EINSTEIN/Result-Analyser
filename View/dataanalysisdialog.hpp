#ifndef DATAANALYSISDIALOG_HPP
#define DATAANALYSISDIALOG_HPP

#include <QDialog>
#include <vector>
#include <string>

using FieldList = std::vector<std::string>;

namespace Ui {
class DataAnalysisDialog;
}

class DataAnalysisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DataAnalysisDialog(QWidget *parent = nullptr, FieldList fields = {});
    ~DataAnalysisDialog();

private slots:
    void on_b_add_field_clicked();

private:
    Ui::DataAnalysisDialog *ui;
    FieldList _fields;

    void setUpExistingFieldsTableWidget();
    void setUpNewFieldsTableWidget();
};

#endif // DATAANALYSISDIALOG_HPP
