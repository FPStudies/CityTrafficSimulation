/*
 * StartScreen.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_START_SCREEN_H
#define TRAFFIC_SIM_START_SCREEN_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <memory>

#include "ScreenInterface.h"
#include "FixedFramerate.h"
#include "CoordinateSystem.h"

#include "../event/Basic.h"
#include "../event/Manager.h"


#include "../drawing/DrawManager.h"

#include "../UI/button/specialization/Exit.h"
#include "../trigger/event/Button.h"
#include "../controls/ControlMapping.h"
#include "../event/Control.h"
#include "../drawing/Texturing.h"
#include "../drawing/font/Manager.h"

class StartScreen: public ScreenInteface{
    std::unique_ptr<b2World> world_;
    std::unique_ptr<Event::Manager> event_manager_;
    std::unique_ptr<sf::View> view_;
    Drawing::Texture::Manager& texture_manager_;
    Drawing::Font::Manager& font_manager_;
    std::unique_ptr<DrawManager> draw_manager_;

    void setBox2D();
    void setEventManager();
    void setTextureManagers(std::shared_ptr<sf::RenderWindow> & window);

public:
    StartScreen();
    ~StartScreen();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;
};


#endif
