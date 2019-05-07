#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <vector>
#include <string>
#include "Utils/settings_data.hpp"

namespace Ui {
class Settings_Dialog;
}


class Settings_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Settings_Dialog(QWidget *parent = nullptr);
    ~Settings_Dialog();

    QString schoolName() const;
    void setSchoolName(const QString &schoolName);

    QString schoolIcon() const;
    void setSchoolIcon(const QString &schoolIcon);

    QString password() const;
    void setPassword(const QString &password);

    int streamsCount() const;
    void setStreamsCount(int streamsCount);

    std::vector<std::string> streamsList() const;
    void setStreamsList(const std::vector<std::string> &streamsList);

    QString newStream() const;
    void setNewStream(const QString &newStream);

    int subjects_count() const;
    void setSubjects_count(int subjects_count);

    std::vector<std::string> subjectsList() const;
    void setSubjectsList(const std::vector<std::string> &subjectsList);

    QString newSubject() const;
    void setNewSubject(const QString &newSubject);

    QString schoolBranch() const;
    void setSchoolBranch(const QString &schoolBranch);



private slots:
    void on_bb_ok_cancel_accepted();

    void on_pb_addStream_clicked();

    void on_pb_addSubject_clicked();

    void on_toolButton_clicked();

signals:
    Settings_Data& Save_Settings(Settings_Data &settings_data);

private:

    Ui::Settings_Dialog *ui;
    QString _schoolName;
    QString _schoolBranch;
    QString _schoolIcon;
    QString _password;
    int _streamsCount;
    std::vector<std::string> _streamsList;
    QString _newStream;
    int _subjects_count;
    std::vector<std::string> _subjectsList;
    QString _newSubject;
};

#endif // SETTINGS_DIALOG_H
