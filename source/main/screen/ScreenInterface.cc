

#include "ScreenInterface.h"

std::unique_ptr<ScreenInterface::LoopbackData> ScreenInterface::received_data_(std::make_unique<ScreenInterface::LoopbackData>());
std::mutex ScreenInterface::lock_loopback_data_;

ScreenInterface::ScreenInterface()
: ID_(ScreenID::newID())
{}

ScreenInterface::~ScreenInterface() = default;

ScreenInterface::LoopbackData::LoopbackData()
: is_anyone_waiting_(false),
close_window_(false),
request_for_next_screen_()
{}

ScreenInterface::LoopbackData::~LoopbackData() = default;

ScreenID ScreenInterface::getID() const{
    return ID_;
}

void ScreenInterface::resetLoopbackData(){
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    auto tmp = new LoopbackData();
    received_data_.reset(tmp);
}

bool ScreenInterface::isAnyoneWaiting(){
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    return received_data_->is_anyone_waiting_;
}

void ScreenInterface::clearAll(){
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    received_data_->request_for_next_screen_.clear();
}

void ScreenInterface::requestForNextScreen(const ScreenID& ID){
    received_data_->is_anyone_waiting_ = true;
    std::lock_guard<std::mutex> guard(lock_loopback_data_);
    received_data_->request_for_next_screen_.push_back(ID);
}

void ScreenInterface::setAsViewed(){
    received_data_->is_anyone_waiting_ = false;
}

void ScreenInterface::resetLoopSynch(Synch::Loop& loopSynch, unsigned int newNumberOfThreads, bool save){
    Synch::Loop::Proxy::reset(loopSynch, newNumberOfThreads, save);
}

void ScreenInterface::prepareLoopSynch(Synch::Loop& loopSynch){
    Synch::Loop::Proxy::prepare(loopSynch);
}

void ScreenInterface::endLoopSynch(Synch::Loop& loopSynch){
    Synch::Loop::Proxy::end(loopSynch);
}

void ScreenInterface::requestCloseWindow(){
    received_data_->is_anyone_waiting_ = true;
    received_data_->close_window_ = true;
}