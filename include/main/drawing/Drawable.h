/*
 * Drawable.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAWABLE_H
#define TRAFFIC_SIM_DRAWABLE_H

#include <SFML/Graphics.hpp>

#include "DrawingID.h"

class Drawable{
    DrawingID ID_;

public:
    Drawable()
    : ID_(DrawingID::newID())
    {}

    virtual ~Drawable() {}


    virtual void draw() = 0;
    virtual sf::FloatRect boundingBox() = 0;
    virtual bool canBeDrawn() = 0;

    DrawingID getID() const{
        return ID_;
    }
};

#endif
