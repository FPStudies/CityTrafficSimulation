#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>

#include "drawingID.h"

class Drawable{
    DrawingID ID;

public:
    Drawable()
    : ID(DrawingID::newID())
    {}

    virtual ~Drawable() {}


    virtual void draw() = 0;
    virtual sf::FloatRect boundingBox() = 0;
    virtual bool canBeDrawn() = 0;

    DrawingID getID() const{
        return ID;
    }
};

#endif