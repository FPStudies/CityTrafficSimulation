/*
 * MainMenu.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_SPECIALIZATION_MAIN_MENU_H
#define TRAFFIC_SIM_MAIN_SCREEN_SPECIALIZATION_MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../ScreenInterface.h"
#include "../FixedFramerate.h"
#include "../ScreenManager.h"

#include "../../synchronization/Loop.h"

#include "../../event/Manager.h"
#include "../../draw/Texturing.h"

#include "../View.h"

#include "../../UI/button/InterfaceDrawTrans.h"
#include "../../UI/button/Buttons.h"

#include "../controls/ControlMapping.h"
#include "../event/Control.h"
#include "../trigger/event/Button.h"
#include "../trigger/action/NextScreen.h"

#include "../event/Basic.h"
#include "../Loopback.h"

namespace Screen::Spec{

class MainMenu: public ScreenInteface{
    unsigned int width_;
    unsigned int height_;
    const ScreenManager& screen_manager_;
    FixedFramerate framerate;

    Draw::Texture::Manager& texture_manager_;
    Draw::Font::Manager& font_manager_;
    Synch::Loop& loop_synch_;

    std::shared_ptr<Screen::View> view_UI_;

    std::unique_ptr<Event::Manager> event_manager_;

    std::unique_ptr<Draw::Manager> draw_manager_;

    std::shared_ptr<Button::Exit> exit_button_;
    std::shared_ptr<Button::Default> sim_button_;
    std::shared_ptr<Draw::Drawable> background_;

    void addButtons(std::shared_ptr<sf::RenderWindow> & window);
    void addBackground(std::shared_ptr<sf::RenderWindow> & window);

public:
    MainMenu(const sf::Vector2u& viewSize, std::shared_ptr<sf::RenderWindow> & window, const ScreenManager& nextScreen);
    MainMenu(unsigned int width, unsigned int height, std::shared_ptr<sf::RenderWindow> & window, const ScreenManager& nextScreen);
    ~MainMenu();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;

};


}




#endif