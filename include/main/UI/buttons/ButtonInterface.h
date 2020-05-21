/*
 * ButtonInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H
#define TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H

#include "../../program_events/EventManager.h"

class ButtonInterface{

public:
    ButtonInterface(EventManager& manager);

    virtual void pressedButton(EventManager& manager) = 0;
    virtual void releasedButton(EventManager& manager) = 0;


};


#endif