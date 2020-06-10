

#include "Loop.h"


Synch::Loop::Loop(const unsigned int& numberOfThreads)
: Utils::SingletonWithCreation<Loop, unsigned int>(), 
number_of_threads_counted_(1),
number_of_threads_(numberOfThreads), 
lock_(),
condition_lock_(),
condition_()
{}

Synch::Loop::~Loop() = default;

void Synch::Loop::enter(){
    lock_.lock();
    if(number_of_threads_counted_ == number_of_threads_){
        number_of_threads_counted_ = 1;
        lock_.unlock();
        condition_.notify_all();
    }
    else{
        ++number_of_threads_counted_;
        lock_.unlock();
        condition_.wait(condition_lock_);
    }
}

void Synch::Loop::Proxy::reset(Loop& loop, unsigned int newNumberOfThreads, bool save){
    std::lock_guard<std::mutex> guard(loop.lock_);
    if(save && loop.number_of_threads_counted_ != 0) throw std::runtime_error("Some threads still did not end. Cannot reset Synch::Loop.");

    loop.number_of_threads_ = newNumberOfThreads;
}