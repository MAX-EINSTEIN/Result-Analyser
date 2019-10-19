#ifndef SINGLETON_FACTORY_HPP
#define SINGLETON_FACTORY_HPP


#include <memory>
#include "Model/settings.h"

template<typename T>
class SingletonFactory final
{
public:
    static T& GetClassAsSingleton();
private:
    static std::unique_ptr<T> _ClassInstance;
    explicit SingletonFactory(const SingletonFactory &rhs) = delete ;
    SingletonFactory &operator= (const SingletonFactory &rhs) = delete;
};

template<typename T>
std::unique_ptr<T> SingletonFactory<T>::_ClassInstance = nullptr;

template<typename T>
T& SingletonFactory<T>::GetClassAsSingleton(){
    if(_ClassInstance == nullptr){
        _ClassInstance = std::unique_ptr<T>(T::returnInstance());
    }
    return *_ClassInstance;
}



#endif // SINGLETON_FACTORY_HPP
