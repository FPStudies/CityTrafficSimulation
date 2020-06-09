
/*
#include "Loopback.h"

using namespace Screen;

Loopback::Loopback() = default;

Loopback::~Loopback() = default;

bool Loopback::isAnyoneWaiting(){
    std::lock_guard<std::mutex> guard(mutex_);

    if(data_->request_for_next_screen_.empty()) return false;

    return true;
}

void Loopback::requestForNextScreen(const ScreenID& ID){
    std::lock_guard<std::mutex> guard(mutex_);
    data_->request_for_next_screen_.push_back(ID);
}

void Loopback::clearAll(){
    std::lock_guard<std::mutex> guard(mutex_);
    data_->request_for_next_screen_.clear();
}*/