/*
 * InstanceProxy.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_INSTANCE_PROXY_H
#define TRAFFIC_SIM_MAIN_SCREEN_INSTANCE_PROXY_H

#include <memory>

namespace Utils{

template<typename ToStore>
class InstanceProxy{
    std::unique_ptr<ToStore> instance_;

public:
    InstanceProxy(const Definition& def)
    : definition_(def), instance_(nullptr)
    {}

    ~InstanceProxy() = default;

    bool create(const ToStore* ptr){
        if(instance_) return true;
        instance_ = std::make_unique<ToStore>(ptr);
        return false;
    }

    void remove(){
        delete instance_;
    }

    ToStore& get(){
        if(instance_) throw std::runtime_error("InstanceProxy do not store any object.");
        return *instance_;
    }

};

}

#endif
