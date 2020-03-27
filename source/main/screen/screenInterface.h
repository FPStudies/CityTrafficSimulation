#ifndef SCREEN_INTERFACE_H
#define SCREEN_INTERFACE_H

#include <SFML/Graphics.hpp>

#include "screenID.h"

class ScreenInteface{
    ScreenID ID;

public:
    virtual ScreenID run(sf::RenderWindow & window) = 0;    // it wll return the next screen that should have been used

    ScreenInteface()
    : ID(ScreenID::State::Valid)
    {}

    virtual ~ScreenInteface() {}

    ScreenID getID() const{
        return ID;
    }
};


#endif