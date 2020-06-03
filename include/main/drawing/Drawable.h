/*
 * Drawable.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_DRAWING_DRAWABLE_H
#define TRAFFIC_SIM_MAIN_DRAWING_DRAWABLE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "DrawingID.h"

class Drawable{
    DrawingID ID_;

public:
    Drawable()
    : ID_(DrawingID::newID())
    {}

    virtual ~Drawable() = default;

    virtual void draw(sf::RenderTarget& target) const = 0;
    virtual sf::FloatRect getLocalBounds() const = 0;
    virtual sf::FloatRect getGlobalBounds() const = 0;
    virtual bool canBeDrawn() const = 0;

    DrawingID getID() const{
        return ID_;
    }

    const DrawingID& getID_const() const{
        return ID_;
    }
};

#endif
