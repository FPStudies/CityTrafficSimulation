

#include "ScreenInterface.h"

std::unique_ptr<ScreenInteface::LoopbackData> ScreenInteface::received_data_(std::make_unique<ScreenInteface::LoopbackData>());
std::mutex ScreenInteface::lock_loopback_data_;


/*
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

ScreenInteface::ScreenInteface()
: ID_(ScreenID::newID())
{}

ScreenInteface::~ScreenInteface() = default;

ScreenID ScreenInteface::getID() const{
    return ID_;
}

void ScreenInteface::resetLoopbackData(){
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    auto tmp = new LoopbackData();
    received_data_.reset(tmp);
}

bool ScreenInteface::isAnyoneWaiting(){
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    if(received_data_->request_for_next_screen_.empty()) return false;

    return true;
}

void ScreenInteface::clearAll(){
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    received_data_->request_for_next_screen_.clear();
}

void ScreenInteface::requestForNextScreen(const ScreenID& ID){
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    received_data_->request_for_next_screen_.push_back(ID);
}