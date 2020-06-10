/*
 * Movable.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_INTERFACE_MOVABLE_H
#define TRAFFIC_SIM_MAIN_INTERFACE_MOVABLE_H

#include <SFML/Graphics.hpp>

#include "../draw/Drawable.h"

namespace Interface{

    // TODO
    class Movable: public Draw::Drawable{

    public:
        Movable() = default;
        ~Movable() = default;
        
        virtual void moveDelta(const sf::Vector2f& delta) = 0;
        virtual void moveAbsolute(const sf::Vector2f& newPosition) = 0;
    };    
}



#endif