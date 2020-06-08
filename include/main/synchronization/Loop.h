/*
 * Loop.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SYNCHRONIZATION_LOOP_H
#define TRAFFIC_SIM_MAIN_SYNCHRONIZATION_LOOP_H

#include <condition_variable>

#include "../utility/Singleton.hpp"

namespace Synch{

class Loop final: public Utils::SingletonWithCreation<Loop, unsigned int>{
    friend class ::Utils::Singleton<Loop>;
    friend class ::Utils::SingletonDestroyer<Loop>;

    unsigned int number_of_threads_counted_;
    unsigned int number_of_threads_;
    std::mutex lock_;
    std::unique_lock<std::mutex> condition_lock_;
    std::condition_variable condition_;

    Loop(const unsigned int& numberOfThreads);
    ~Loop();

public:
    Loop(const Loop&) = delete;
    Loop(Loop&&) = delete;
    Loop& operator=(const Loop&) = delete;
    Loop& operator=(Loop&&) = delete;


    void enter();



};

}

#endif
