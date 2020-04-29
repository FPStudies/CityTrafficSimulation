#ifndef ZPR_TRAFFIC_SIM_START_SCREEN_H
#define ZPR_TRAFFIC_SIM_START_SCREEN_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <memory>

#include "screenInterface.h"

#include "../program_events/eventManager.h"
#include "../program_events/basicEvents.h"

#include "../drawing/drawManager.h"

class StartScreen: virtual public ScreenInteface{
    std::unique_ptr<b2World> world;
    std::unique_ptr<EventManager> eventManager;

    void setBox2D();
    void setEventManager();

public:
    StartScreen();
    ~StartScreen();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;
};


#endif