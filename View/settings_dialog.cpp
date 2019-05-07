#include "settings_dialog.h"
#include "ui_settings_dialog.h"
#include <QDir>
#include <QFileDialog>

Settings_Dialog::Settings_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings_Dialog)
{
    ui->setupUi(this);
}

Settings_Dialog::~Settings_Dialog()
{
    delete ui;
}

QString Settings_Dialog::schoolName() const
{
    return _schoolName;
}

void Settings_Dialog::setSchoolName(const QString &schoolName)
{
    _schoolName = schoolName;
    ui->le_schoolName->setText(_schoolName);
}

QString Settings_Dialog::schoolBranch() const
{
    return _schoolBranch;
}

void Settings_Dialog::setSchoolBranch(const QString &schoolBranch)
{
    _schoolBranch = schoolBranch;
    ui->le_schoolBranch->setText(_schoolBranch);
}


QString Settings_Dialog::schoolIcon() const
{
    return _schoolIcon;
}

void Settings_Dialog::setSchoolIcon(const QString &schoolIcon)
{
    _schoolIcon = schoolIcon;
    ui->tb_Icon->setSource(QUrl(_schoolIcon));
}

QString Settings_Dialog::password() const
{
    return _password;
}

void Settings_Dialog::setPassword(const QString &password)
{
    _password = password;
    ui->le_password->setText(_password);
}

int Settings_Dialog::streamsCount() const
{
    return _streamsCount;
}

void Settings_Dialog::setStreamsCount(int streamsCount)
{
    _streamsCount = streamsCount;
    ui->l_stream_count->setNum(_streamsCount);
}

std::vector<std::string> Settings_Dialog::streamsList() const
{
    return _streamsList;
}

void Settings_Dialog::setStreamsList(const std::vector<std::string> &streamsList)
{
    _streamsList = streamsList;
    for(auto item:_streamsList)
        ui->lw_streams->addItem(item.c_str());
}

QString Settings_Dialog::newStream() const
{
    return _newStream;
}

void Settings_Dialog::setNewStream(const QString &newStream)
{
    _newStream = newStream;
}

int Settings_Dialog::subjects_count() const
{
    return _subjects_count;
}

void Settings_Dialog::setSubjects_count(int subjects_count)
{
    _subjects_count = subjects_count;
    ui->l_subject_count->setNum(_subjects_count);
}

std::vector<std::string> Settings_Dialog::subjectsList() const
{
    return _subjectsList;
}

void Settings_Dialog::setSubjectsList(const std::vector<std::string> &subjectsList)
{
    _subjectsList = subjectsList;
    for(auto item:_subjectsList)
        ui->lw_Subjects->addItem(item.c_str());
}

QString Settings_Dialog::newSubject() const
{
    return _newSubject;
}

void Settings_Dialog::setNewSubject(const QString &newSubject)
{
    _newSubject = newSubject;
}


void Settings_Dialog::on_bb_ok_cancel_accepted()
{
    Settings_Data &new_settings_data = *(new Settings_Data());

    new_settings_data._schoolName = ui->le_schoolName->text();
    setSchoolName(ui->le_schoolName->text());
    new_settings_data._schoolBranch = ui->le_schoolBranch->text();
    setSchoolBranch(ui->le_schoolBranch->text());
    //new_settings_data._schoolIcon = ui->tb_Icon->source().toString();
    //setSchoolIcon(ui->tb_Icon->source().toString());
    new_settings_data._password = ui->le_password->text();
    setPassword(ui->le_password->text());
    for(int i=0; i < ui->lw_streams->count();i++)
    {
        new_settings_data._streamsList.clear();
        new_settings_data._streamsList.push_back(ui->lw_streams->item(i)->text().toStdString());
    }
    setStreamsCount(int(new_settings_data._streamsList.size()));
    new_settings_data._streamsCount = streamsCount();
    setStreamsList(new_settings_data._streamsList);
    for(int i=0; i < ui->lw_Subjects->count();i++)
    {
        new_settings_data._subjectsList.clear();
        new_settings_data._subjectsList.push_back(ui->lw_Subjects->item(i)->text().toStdString());
    }
    setSubjects_count(int(new_settings_data._subjectsList.size()));
    new_settings_data._subjects_count = subjects_count();
    setSubjectsList(new_settings_data._subjectsList);

    emit Save_Settings(new_settings_data);
}


void Settings_Dialog::on_pb_addStream_clicked()
{
    ui->lw_streams->addItem(ui->le_stream_name->text());
    setStreamsCount(streamsCount()+1);
}


void Settings_Dialog::on_pb_addSubject_clicked()
{
    ui->lw_Subjects->addItem(ui->le_subject_name->text());
    setSubjects_count(subjects_count()+1);
}

void Settings_Dialog::on_toolButton_clicked()
{
    //setSchoolIcon(QFileDialog::getOpenFileName(this,"Choose an icon file",QDir::homePath(),"PNG(*.png) ;; JPEG (*.jpeg) ;; JPG (*.jpg) ;; ICON (*.ico)"));
}
