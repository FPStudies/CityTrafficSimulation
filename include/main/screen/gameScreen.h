#ifndef ZPR_TRAFFIC_SIM_GAME_SCREEN_H
#define ZPR_TRAFFIC_SIM_GAME_SCREEN_H

#include "screenInterface.h"

class GameScreen: public ScreenInteface{
    // TODO
public:
    ScreenID run(std::shared_ptr<sf::RenderWindow>& window);
};


#endif