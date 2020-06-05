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

#include "../UI/button/specialization/Exit.h"
#include "../trigger/event/Button.h"
#include "../controls/ControlMapping.h"
#include "../event/Control.h"
#include "../draw/Texturing.h"
#include "../elements/Road.h"

class StartScreen: public ScreenInteface{
    std::unique_ptr<b2World> world_;
    std::unique_ptr<Event::Manager> event_manager_;
    std::shared_ptr<sf::View> view_world_;
    std::shared_ptr<sf::View> view_UI_;
    Draw::Texture::Manager& texture_manager_;
    Draw::Font::Manager& font_manager_;
    std::unique_ptr<Draw::Manager> draw_manager_;

    void setBox2D();
    void setEventManager();
    void setTextureManagers(std::shared_ptr<sf::RenderWindow> & window);
    void addExitButton(std::shared_ptr<Button::Exit>& exit_button, std::shared_ptr<sf::RenderWindow> & window);
    void addTextToButton(std::shared_ptr<Button::Exit>& exit_button);

public:
    StartScreen();
    ~StartScreen();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;
};


#endif
