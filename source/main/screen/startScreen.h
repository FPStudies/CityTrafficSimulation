#ifndef START_SCREEN_H
#define START_SCREEN_H

#include "screenInterface.h"

class StartScreen: public ScreenInteface{
    
public:
    ScreenID run(sf::RenderWindow & window);
};


#endif