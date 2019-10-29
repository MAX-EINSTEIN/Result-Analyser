#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <QObject>

#include "Model/settings.hpp"
#include "Utils/singleton_factory.hpp"
#include "View/loginwindow.hpp"
#include "View/mainview.hpp"
#include "View/classes.hpp"
#include "View/settingsdialog.hpp"
#include "View/dataanalysisdialog.hpp"


class Application_Manager:public QObject
{
    Q_OBJECT

public:
    Application_Manager();
    void startProgram();

private:
    Settings &_appSettings;
    LoginWindow * _loginScreen;
    MainView * _mainScreen;
    Classes * _sidebarPanel;
    Settings_Dialog * _settingsScreen;

    void initSettings();
    void setupWindows();
};

#endif // SETTINGS_MANAGER_H
