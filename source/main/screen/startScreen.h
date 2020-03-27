#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <SFML/Graphics.hpp>

#include "screenInterface.h"

#include "../program_events/eventManager.h"
#include "../program_events/basicEvents.h"

class StartScreen: public ScreenInteface{
    
public:
    StartScreen();
    ~StartScreen();

    ScreenID run(sf::RenderWindow & window);
};


#endif