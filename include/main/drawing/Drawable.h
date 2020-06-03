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

class Drawable: public sf::Drawable{
    DrawingID ID_;

    // reminding to define it
    virtual void draw(sf::RenderTarget& target, sf::RenderStates& states) const = 0;

public:
    Drawable()
    : ID_(DrawingID::newID())
    {}

    virtual ~Drawable() = default;

    
    virtual const sf::FloatRect& boundingBox() const = 0;
    virtual bool canBeDrawn() const = 0;

    virtual sf::RenderStates& getRenderStates() const = 0;

    DrawingID getID() const{
        return ID_;
    }

    const DrawingID& getID_const() const{
        return ID_;
    }
};

#endif
