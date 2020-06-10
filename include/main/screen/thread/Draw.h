/*
 * Draw.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_THREAD_DRAW_H
#define TRAFFIC_SIM_MAIN_SCREEN_THREAD_DRAW_H

#include <SFML/Graphics.hpp>

#include "FixedFramerate.h"

#include "../draw/Texturing.h"

#include "../../synchronization/Loop.h"

#include "Interface.h"

namespace Thread{

class Draw: public ::Thread::Inteface{
    std::shared_ptr<sf::RenderWindow> window_;
    ::Draw::Manager& draw_manager_;
    ::Synch::Loop& loop_synch_;

public:
    Draw(const std::shared_ptr<sf::RenderWindow> & window, ::Draw::Manager& drawManager, ::Synch::Loop& loopSynch, Communication& comm);
    ~Draw();

    void operator()();

};
}

#endif
