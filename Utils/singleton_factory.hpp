#ifndef SINGLETON_FACTORY_HPP
#define SINGLETON_FACTORY_HPP


#include <memory>
#include "Model/settings.h"

class Singleton_Factory final
{
public:
    static Settings& GetSettingsAsSingleton();
private:
    static std::unique_ptr<Settings> _SettingsInstance;
    explicit Singleton_Factory(const Singleton_Factory &rhs) = delete ;
    Singleton_Factory &operator= (const Singleton_Factory &rhs) = delete ;
};

#endif // SINGLETON_FACTORY_HPP
