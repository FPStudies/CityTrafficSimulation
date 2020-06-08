/*
 * Loopback.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_LOOPBACK_H
#define TRAFFIC_SIM_MAIN_SCREEN_LOOPBACK_H

#include <vector>

#include "../utility/Singleton.hpp"
#include "ScreenID.h"

namespace Screen{


/**
 * @brief A communication method with the calling screen.
 * Any object can request something to the screen.
 */
class Loopback final: public ::Utils::Singleton<Loopback>{
    friend class ::Utils::Singleton<Loopback>;
    friend class ::Utils::SingletonDestroyer<Loopback>;
    friend class ScreenInterface;

    /*
    * There can be a plethora of things that some object could want to deliver to the screen.
    * One of these things are next screen ID.
    */
    std::vector<ScreenID> request_for_next_screen_;

    Loopback();
    ~Loopback();

public:    

    bool isAnyoneWaiting();

    void requestForNextScreen(const ScreenID& ID);

    void clearAll();

};

}

#endif
