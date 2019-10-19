#ifndef SETTINGS_DATA_HPP
#define SETTINGS_DATA_HPP

#include <vector>
#include <string>
#include <QString>

struct Settings_Data{
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

#endif // SETTINGS_DATA_HPP
