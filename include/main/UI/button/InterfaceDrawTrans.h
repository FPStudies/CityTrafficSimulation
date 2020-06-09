/*
 * InterfaceDrawTrans.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UI_BUTTON_INTERFACE_DRAW_TRANS_H
#define TRAFFIC_SIM_MAIN_UI_BUTTON_INTERFACE_DRAW_TRANS_H


#include <SFML/Graphics.hpp>
#include <vector>

#include "InterfaceDraw.h"

namespace Button{
    class InterfaceDrawTrans: public InterfaceDraw, public sf::Transformable{
        
    };
}




#endif