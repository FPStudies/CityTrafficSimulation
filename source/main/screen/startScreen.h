#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <SFML/Graphics.hpp>

#include "screenInterface.h"

#include "../program_events/eventManager.h"
#include "../program_events/basicEvents.h"

#include "../drawing/drawManager.h"

class StartScreen: virtual public ScreenInteface{
    
public:
    StartScreen();
    ~StartScreen();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;
};


#endif