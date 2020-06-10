/*
 * Interface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_THREAD_INTERFACE_H
#define TRAFFIC_SIM_MAIN_SCREEN_THREAD_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <mutex>
#include <memory>
#include <atomic>

#include "../ScreenID.h"
#include "../../utility/Singleton.hpp"

namespace Thread{

/**
 * @brief Interface used by the classes that are used to create new threads.
 * 
 */
class Inteface{
public:
    /**
     * @brief Struct used to communicate with other threads.
     * 
     */
    struct Communication{
        /**
         * @brief Flag used to communicate when the threads should end.
         */
        std::atomic<bool> is_active_;

        Communication()
        : is_active_(true)
        {}

        ~Communication() = default;
    };

protected:
    Communication& thread_communication_;

public:
    Inteface(Communication& comm)
    : thread_communication_(comm)
    {}

    ~Inteface() = default;
};

}

#endif
