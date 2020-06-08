/*
 * InterfaceDraw.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UI_BUTTON_INTERFACE_DRAW_H
#define TRAFFIC_SIM_MAIN_UI_BUTTON_INTERFACE_DRAW_H


#include <SFML/Window.hpp>
#include <vector>

#include "Interface.h"

namespace Button{
    class InterfaceDraw: public Interface, public Draw::Drawable{
        
    };
}




#endif