#ifndef SCREEN_INTERFACE_H
#define SCREEN_INTERFACE_H

#include <SFML/Graphics.hpp>

#include "screenID.h"

class ScreenInteface: public ScreenID{
    
public:
    virtual ScreenID run(sf::RenderWindow & window) = 0;
};


#endif