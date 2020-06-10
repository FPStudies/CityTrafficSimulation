/*
 * Loop.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SYNCHRONIZATION_LOOP_H
#define TRAFFIC_SIM_MAIN_SYNCHRONIZATION_LOOP_H

#include <condition_variable>

#include "../utility/Singleton.hpp"

class ScreenInteface;

namespace Synch{

class Loop final: public Utils::SingletonWithCreation<Loop, unsigned int>{
    friend class ::Utils::SingletonWithCreation<Loop, unsigned int>;
    friend class ::Utils::SingletonDestroyer<Loop>;
    friend class Proxy;

    unsigned int number_of_threads_counted_;
    unsigned int number_of_threads_;
    bool active_;
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

    class Proxy{
        friend class ::ScreenInteface;
        
        static void reset(Loop& loop, unsigned int newNumberOfThreads, bool save = true);

        static bool prepare(Loop& loop);

        static bool end(Loop& loop);
    };

};

}

#endif
