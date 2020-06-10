/*
 * GameScreen.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_GAME_SCREEN_H
#define TRAFFIC_SIM_MAIN_SCREEN_GAME_SCREEN_H

#include "ScreenInterface.h"

class GameScreen: public ScreenInterface{
    // TODO:
public:
    ScreenID run(std::shared_ptr<sf::RenderWindow>& window);
};


#endif
