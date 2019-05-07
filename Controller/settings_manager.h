#ifndef SETTINGS_MANAGER_H
#define SETTINGS_MANAGER_H

#include <QObject>

#include "Model/settings.h"
#include "Utils/singleton_factory.hpp"
#include "View/loginwindow.h"
#include "View/mainview.h"
#include "View/classes.h"
#include "View/settings_dialog.h"


class Settings_Manager:public QObject
{
    Q_OBJECT

public:
    Settings_Manager();
    void StartProgram();

private:
    Settings &_appSettings;
    LoginWindow * _loginScreen;
    MainView * _mainScreen;
    Classes * _sidebarPanel;
    Settings_Dialog * _settingsScreen;

    void InitSettings();
    void SetupWindows();
};

#endif // SETTINGS_MANAGER_H
