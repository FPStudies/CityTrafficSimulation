/*
 * Drawable.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_DRAWING_DRAWABLE_H
#define TRAFFIC_SIM_MAIN_DRAWING_DRAWABLE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "DrawID.h"

namespace Draw{

/**
 * @brief Interface that is used by Draw::Manager to store elements, that can be drawn.
 * 
 */
class Drawable{
    DrawID ID_;

public:
    Drawable()
    : ID_(DrawID::newID())
    {}

    virtual ~Drawable() = default;

    virtual void draw(sf::RenderTarget& target) const = 0;
    virtual sf::FloatRect getLocalBounds() const = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual bool canBeDrawn() const = 0;

    DrawID getID() const{
        return ID_;
    }

    const DrawID& getID_const() const{
        return ID_;
    }
};
}

#endif
