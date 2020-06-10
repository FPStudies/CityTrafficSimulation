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

#include "ScreenID.h"
#include "../utility/Singleton.hpp"

namespace Thread{


class Inteface{
public:
    struct Communication{
        std::atomic<bool> is_active_;
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
