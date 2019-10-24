#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QStringListModel>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QStandardPaths>
#include <utility>
#include <vector>
#include <string>
#include "Utils/settings_data.hpp"

typedef std::pair<QJsonObject,QJsonParseError> JsonObjErrPair;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent, QString filename);
    void parseJsonData();
    void setJsonDocument();
    static Settings* returnInstance();

    QString filename() const;

    QString applicationTitle() const;

    QString appShortTitle() const;

    QString password() const;
    void setPassword(const QString &password);

    int maxSections() const;
    void setMaxSections(int maxSections);

    int maxSubjects() const;
    void setMaxSubjects(int maxSubjects);

    QString schoolName() const;
    void setSchoolName(const QString &schoolName);

    QString schoolIcon() const;
    void setSchoolIcon(const QString &schoolIcon);

    int maxStreams() const;
    void setMaxStreams(int maxStreams);

    QString schoolBranch() const;
    void setSchoolBranch(const QString &schoolBranch);

    std::vector<std::string> streamsList() const;
    void setStreamsList(const std::vector<std::string> &streamsList);

    std::vector<std::string> subjectsList() const;
    void setSubjectsList(const std::vector<std::string> &subjectsList);

signals:
    void notifyStatusMessage(QString msg);

public slots:
    void saveNewConfiguration(Settings_Data &Data);

private:
    QString _filename;
    QString _applicationTitle;
    QString _appShortTitle;
    QString _schoolName;
    QString _schoolBranch;
    QString _schoolIcon;
    QString _password;
    int _maxSections;
    int _maxStreams;
    std::vector<std::string> _streamsList;
    int _maxSubjects;
    std::vector<std::string> _subjectsList;

    QJsonDocument _jsonDoc;
    QJsonObject _jsonObject;
    QString _newSettings;


    QString readJsonFile();
    void writeJsonFile();
    QString readJsonFromInternalResource();
    void writeJsonToInternalResource();
    QDir openConfigDirectory();
    void writeDefaultsToStdConfigFile(QFile &file,const QString &settings);
    JsonObjErrPair getJsonObject(const QString &raw_json);
    void fillStringLists(std::vector<std::string> &list,QJsonArray arr);
    void sendErrorMessage(const QString& msg);
    void showJasonParseError(QJsonParseError &json_error);

    explicit Settings(const Settings &s) = delete ;
    Settings& operator= (const Settings &s) = delete;

};

#endif // SETTINGS_H
