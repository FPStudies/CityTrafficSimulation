/*
 * Loopback.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_LOOPBACK_H
#define TRAFFIC_SIM_MAIN_SCREEN_LOOPBACK_H
/*
#include <vector>
#include <mutex>

#include "../utility/Singleton.hpp"
#include "ScreenID.h"
#include "ScreenInterface.h"

namespace Screen{



class Loopback final: public ::Utils::Singleton<Loopback>{
    friend class ::Utils::Singleton<Loopback>;
    friend class ::Utils::SingletonDestroyer<Loopback>;
    friend class ScreenInterface;

    std::mutex mutex_;

    std::unique_ptr<ScreenInteface::LoopbackData> data_;

    Loopback();
    ~Loopback();

public:    

    bool isAnyoneWaiting();

    void requestForNextScreen(const ScreenID& ID);

    void clearAll();

};

}*/

#endif
