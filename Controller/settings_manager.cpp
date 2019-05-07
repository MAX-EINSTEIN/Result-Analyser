#include "settings_manager.h"

Settings_Manager::Settings_Manager():
    _appSettings(Singleton_Factory::GetSettingsAsSingleton()),
    _loginScreen(new LoginWindow(nullptr)),
    _mainScreen(nullptr),
    _sidebarPanel(nullptr)
{

}

void Settings_Manager::StartProgram()
{
    SetupWindows();
}


void Settings_Manager::InitSettings()
{
    _appSettings.ParseJsonData();
}




void Settings_Manager::SetupWindows()
{
    InitSettings();

    _mainScreen = new MainView(nullptr);

    // Setting up sidebar Panel
    _sidebarPanel = new Classes(_mainScreen);
    _sidebarPanel->setSections(_appSettings.maxSections());

    // Setting up settings Dialog
    _settingsScreen = new Settings_Dialog(_mainScreen);
    _settingsScreen->setSchoolName(_appSettings.schoolName());
    _settingsScreen->setSchoolBranch(_appSettings.schoolBranch());
    //_settingsScreen->setSchoolIcon(_appSettings.schoolIcon());
    _settingsScreen->setPassword(_appSettings.password());
    _settingsScreen->setStreamsCount(_appSettings.maxStreams());
    _settingsScreen->setStreamsList(_appSettings.streamsList());
    _settingsScreen->setSubjects_count(_appSettings.maxSubjects());
    _settingsScreen->setSubjectsList(_appSettings.subjectsList());


    // Setting up MainView
    _mainScreen->setSidebar(_sidebarPanel);
    _mainScreen->setMaxStreams(4);
    _mainScreen->setSplitter(_appSettings.streamsList(),_appSettings.subjectsList());
    _mainScreen->setSettings(_settingsScreen);

    // Setting up login Window
    _loginScreen->setPassword(_appSettings.password());
    _loginScreen->setChild_Window(_mainScreen);
    _loginScreen->show();


    connect(_settingsScreen,SIGNAL(Save_Settings(Settings_Data&)),&_appSettings,SLOT(SaveNewConfiguration(Settings_Data&)));
}
