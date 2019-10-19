#include "settings.h"

static  QString RESOURCE_PREFIX = QStringLiteral(":/files/Files");
static const QString SETTINGS_FILE = QStringLiteral("Settings.json");


Settings::Settings(QObject *parent, QString filename):
    QObject (parent),
    _filename(filename)
{

}


void Settings::ParseJsonData()
{
    QString raw_json = ReadJsonFile();
    if(raw_json.size() == 0)return;

    JsonObjErrPair result = GetJsonObject(raw_json);
    QJsonParseError json_error = result.second;
    if(json_error.error != QJsonParseError::NoError)
    {
        ShowJasonParseError(json_error);
    }

    _jsonObject = result.first;

    _applicationTitle = _jsonObject["applicationTitle"].toString();
    _appShortTitle = _jsonObject["appShortTitle"].toString();
    _schoolName = _jsonObject["schoolName"].toString();
    _schoolBranch = _jsonObject["schoolBranch"].toString();
    _schoolIcon = _jsonObject["schoolIcon"].toString();
    _password = _jsonObject["password"].toString();
    _maxSections = _jsonObject["maxSections"].toInt();
    _maxStreams = _jsonObject["maxStreams"].toInt();
    FillStringLists(_streamsList,_jsonObject["streams"].toArray());
    _maxSubjects = _jsonObject["maxSubjects"].toInt();
    FillStringLists(_subjectsList,_jsonObject["subjects"].toArray());
}


QString Settings::filename() const
{
    return _filename;
}


QString Settings::applicationTitle() const
{
    return _applicationTitle;
}


QString Settings::appShortTitle() const
{
    return _appShortTitle;
}


QString Settings::password() const
{
    return _password;
}


void Settings::setPassword(const QString &password)
{
    _password = password;
    _jsonObject["password"] = _password;
}


int Settings::maxSections() const
{
    return _maxSections;
}


void Settings::setMaxSections(int maxSections)
{
    _maxSections = maxSections;
    _jsonObject["maxSections"] = _maxSections;
}


int Settings::maxSubjects() const
{
    return _maxSubjects;
}


void Settings::setMaxSubjects(int maxSubjects)
{
    _maxSubjects = maxSubjects;
    _jsonObject["maxSubjects"] = _maxSubjects;
}


QString Settings::schoolName() const
{
    return _schoolName;
}


void Settings::setSchoolName(const QString &schoolName)
{
    _schoolName = schoolName;
    _jsonObject["schoolName"] = _schoolName;
}


QString Settings::schoolIcon() const
{
    return _schoolIcon;
}


void Settings::setSchoolIcon(const QString &schoolIcon)
{
    _schoolIcon = schoolIcon;
    _jsonObject["schoolIcon"] = _schoolIcon;
}


int Settings::maxStreams() const
{
    return _maxStreams;
}


void Settings::setMaxStreams(int maxStreams)
{
    _maxStreams = maxStreams;
    _jsonObject["maxStreams"] = _maxStreams;
}


QString Settings::schoolBranch() const
{
    return _schoolBranch;
}


void Settings::setSchoolBranch(const QString &schoolBranch)
{
    _schoolBranch = schoolBranch;
    _jsonObject["schoolBranch"] = _schoolBranch;
}


std::vector<std::string> Settings::streamsList() const
{
    return _streamsList;
}


void Settings::setStreamsList(const std::vector<std::string> &streamsList)
{
    _streamsList = streamsList;
    QJsonArray temp;
    for(auto item:_streamsList)
        temp.append(item.c_str());
    _jsonObject["streams"] = temp;
}


std::vector<std::string> Settings::subjectsList() const
{
    return _subjectsList;
}


void Settings::setSubjectsList(const std::vector<std::string> &subjectsList)
{
    _subjectsList = subjectsList;
    QJsonArray temp;
    for(auto item:_subjectsList)
        temp.append(item.c_str());
    _jsonObject["subjects"] = temp;
}


QString Settings::ReadJsonFile()
{
    QString default_Settings = ReadJsonFromInternalResource();
    QDir config_dir = OpenConfigDirectory();
    QFile std_file(config_dir.filePath(_filename));
    if(std_file.exists())
    {
        if(!std_file.open((QFile::ReadOnly | QFile::Text)))
        {
            SendErrorMessage("Cannot Open Config File");
            return  default_Settings;
        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    }
    else
    {
        WriteDefaultsToStdConfigFile(std_file,default_Settings);
        return  default_Settings;
    }
}


void Settings::WriteJsonFile()
{
    QDir config_dir = OpenConfigDirectory();
    QFile std_file(config_dir.filePath(_filename));
    if(std_file.exists())
    {
        if(!std_file.remove())
        {
            SendErrorMessage("Cannot Delete Config File");
            return;
        }
    }
    std_file.close();

    int length = _newSettings.length();
    if(!std_file.open(QFile::WriteOnly | QFile::Text))
    {
        SendErrorMessage("Cannot Open Config File " + std_file.fileName());
    }

    long long bytes_written = std_file.write(qPrintable(_newSettings),length);
    if(bytes_written != length)
    {
        SendErrorMessage("Cannot write to File " + std_file.fileName());
        if(!std_file.remove())
        {
            SendErrorMessage("Cannot Remove config file. Please delete the file manually. FilePath : "+std_file.fileName());
        }
    }
    std_file.close();
}


QString Settings::ReadJsonFromInternalResource()
{
    QDir res_dir(RESOURCE_PREFIX);
    if(!res_dir.exists())
    {
        SendErrorMessage("Cannot find internal path " + res_dir.canonicalPath());
        return "";
    }
    QString path = res_dir.filePath(_filename);
    QFile res_file(path);
    if(!res_file.open(QFile::ReadOnly | QFile::Text))
    {
        SendErrorMessage("No file named " + path + " found");
        return "";
    }
    QString Settings = res_file.readAll();
    res_file.close();
    return Settings;
}


void Settings::WriteJsonToInternalResource()
{
    QDir res_dir(RESOURCE_PREFIX);
    if(!res_dir.exists())
    {
        SendErrorMessage("Cannot find internal path " + res_dir.canonicalPath());
    }
    QString path = res_dir.filePath(_filename);
    QFile res_file(path);

    if(!res_file.open(QFile::WriteOnly | QFile::Text))
    {
        SendErrorMessage("Cannot Open Config File " + res_file.fileName());
    }

    int length = _newSettings.length();

    long long bytes_written = res_file.write(qPrintable(_newSettings),length);
    if(bytes_written != length)
    {
        SendErrorMessage("Cannot write to File " + res_file.fileName());
        if(!res_file.remove())
        {
            SendErrorMessage("Cannot Remove config file. Please delete the file manually. FilePath : "+res_file.fileName());
        }
    }
    res_file.close();
}


QDir Settings::OpenConfigDirectory()
{
    QDir config_dir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation));
    if(!config_dir.exists())
    {
        QDir dir;
        dir.mkpath(config_dir.path());
    }
    return config_dir;
}


void Settings::WriteDefaultsToStdConfigFile(QFile &file, const QString &settings)
{
    int length = settings.length();
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        SendErrorMessage("Cannot Open Config File " + file.fileName());
    }

    long long bytes_written = file.write(qPrintable(settings),length);
    if(bytes_written != length)
    {
        SendErrorMessage("Cannot write to File " + file.fileName());
        if(!file.remove())
        {
            SendErrorMessage("Cannot Remove config file. Please delete the file manually. FilePath : "+file.fileName());
        }
    }
    file.close();
}


JsonObjErrPair Settings::GetJsonObject(const QString &raw_json)
{
    QJsonParseError json_parse_error;
    _jsonDoc = QJsonDocument::fromJson(raw_json.toUtf8(),&json_parse_error);
    QJsonObject json_obj = _jsonDoc.object();
    return std::make_pair(json_obj,json_parse_error);
}


void Settings::SetJsonDocument()
{
    _jsonDoc = *new QJsonDocument(_jsonObject);
    _newSettings = _jsonDoc.toJson();
}

Settings* Settings::returnInstance()
{
    return new Settings(nullptr,SETTINGS_FILE);
}


void Settings::SaveNewConfiguration(Settings_Data &Data)
{
    _jsonObject["schoolName"] = Data._schoolName;
    _jsonObject["schoolBranch"] = Data._schoolBranch;
    //_jsonObject["schoolIcon"] = Data._schoolIcon;
    _jsonObject["password"] = Data._password;
    _jsonObject["maxStreams"] = Data._streamsCount;
    _jsonObject["maxSubjects"] = Data._subjects_count;

    setStreamsList(Data._streamsList);
    setSubjectsList(Data._subjectsList);

    SetJsonDocument();

    WriteJsonFile();
}


void Settings::FillStringLists(std::vector<std::string> &list, QJsonArray arr)
{
    for(auto item:arr)
        list.push_back(item.toString().toStdString());
}


void Settings::SendErrorMessage(const QString &msg)
{
    emit NotifyStatusMessage(msg);
}


void Settings::ShowJasonParseError(QJsonParseError &json_error)
{
    QString msg = tr("Error Parsing Json Document");
    msg.append(json_error.errorString());
    QMessageBox::critical(nullptr,"Parse Error",msg.toStdString().c_str());
}


