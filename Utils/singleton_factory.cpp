#include "Utils/singleton_factory.hpp"

static QString SETTINGS_FILE = QStringLiteral("Settings.json");
std::unique_ptr<Settings> Singleton_Factory::_SettingsInstance = nullptr;


Settings &Singleton_Factory::GetSettingsAsSingleton()
{
    if(_SettingsInstance == nullptr)
    {
        _SettingsInstance = std::unique_ptr<Settings>(new Settings(nullptr,SETTINGS_FILE));
    }
    return  *_SettingsInstance;
}
