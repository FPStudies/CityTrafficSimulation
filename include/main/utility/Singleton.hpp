/*
 * Singleton.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UTILS_SINGLETON_HPP
#define TRAFFIC_SIM_MAIN_UTILS_SINGLETON_HPP

#include <mutex>

namespace Utils{

template<typename Singleton>
class SingletonDestroyer{
    Singleton* instance_;

public:
    SingletonDestroyer(Singleton* instance = nullptr)
    : instance_(instance)
    {}

    ~SingletonDestroyer(){
        delete instance_;
    }

    void setSingleton(Singleton* instance){
        instance_ = instance;
    }
};

template<typename OtherClass, typename DataStruct>
class SingletonWithCreation{
    friend class Utils::SingletonDestroyer<OtherClass>;

    static OtherClass* instance_;
    static Utils::SingletonDestroyer<OtherClass> destroyer_;
    static std::mutex mutex_instance_;

    SingletonWithCreation(SingletonWithCreation&&) = delete;
    SingletonWithCreation(const SingletonWithCreation&) = delete;
    SingletonWithCreation& operator=(const SingletonWithCreation&) = delete;
    SingletonWithCreation& operator=(SingletonWithCreation&&) = delete;
    
public:
    SingletonWithCreation() = default;
    ~SingletonWithCreation() = default;

    static OtherClass& create(const DataStruct& data){
        if(!instance_){
            const std::lock_guard<std::mutex> lock(mutex_instance_);
            if(!instance_){
                instance_ = new OtherClass(data);
                destroyer_.setSingleton(instance_);
            }
        }
        return *instance_;
    }

    static OtherClass& getInstance(){
        if(!instance_){
            throw std::runtime_error("Singleton is not created. Cannot get instance.");
        }
        return *instance_;
    }

};

template<typename OtherClass, typename DataStruct>
OtherClass* SingletonWithCreation<OtherClass, DataStruct>::instance_ = nullptr;

template<typename OtherClass, typename DataStruct>
Utils::SingletonDestroyer<OtherClass> SingletonWithCreation<OtherClass, DataStruct>::destroyer_;

template<typename OtherClass, typename DataStruct>
std::mutex SingletonWithCreation<OtherClass, DataStruct>::mutex_instance_;







template<typename OtherClass>
class Singleton{
    friend class Utils::SingletonDestroyer<OtherClass>;

    static OtherClass* instance_;
    static Utils::SingletonDestroyer<OtherClass> destroyer_;
    static std::mutex mutex_instance_;

    
    Singleton(Singleton&&) = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    
public:
    Singleton() = default;
    ~Singleton() = default;

    static OtherClass& getInstance(){
        if(!instance_){
            const std::lock_guard<std::mutex> lock(mutex_instance_);
            if(!instance_){
                instance_ = new OtherClass;
                destroyer_.setSingleton(instance_);
            }
        }
        return *instance_;
    }

};

template<typename OtherClass>
OtherClass* Singleton<OtherClass>::instance_ = nullptr;

template<typename OtherClass>
Utils::SingletonDestroyer<OtherClass> Singleton<OtherClass>::destroyer_;

template<typename OtherClass>
std::mutex Singleton<OtherClass>::mutex_instance_;

}

#endif
