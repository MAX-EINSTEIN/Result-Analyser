#include "application_manager.hpp"

Application_Manager::Application_Manager():
    _appSettings(SingletonFactory<Settings>::GetClassAsSingleton()),
    _loginScreen(new LoginWindow(nullptr)),
    _mainScreen(nullptr),
    _sidebarPanel(nullptr)
{

}

void Application_Manager::startProgram()
{
    setupWindows();
}


void Application_Manager::initSettings()
{
    _appSettings.parseJsonData();
}


void Application_Manager::setupWindows()
{
    initSettings();

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
    _mainScreen->setSettings(_settingsScreen);

    // Setting up login Window
    _loginScreen->setPassword(_appSettings.password());
    _loginScreen->setChild_Window(_mainScreen);
    _loginScreen->show();


    connect(_settingsScreen,SIGNAL(saveSettings(Settings_Data&)),&_appSettings,SLOT(saveNewConfiguration(Settings_Data&)));
}
