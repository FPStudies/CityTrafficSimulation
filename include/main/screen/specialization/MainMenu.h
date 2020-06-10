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

#include "../../UI/button/Interface.h"
#include "../../UI/button/Buttons.h"

#include "../controls/ControlMapping.h"
#include "../event/Control.h"
#include "../trigger/event/Button.h"
#include "../trigger/action/NextScreen.h"

#include "../UI/tiles/Background.h"
#include "../thread/Draw.h"

#include "../event/Basic.h"

namespace ScreenMaster::Spec{

/**
 * @brief Screen that represent the menu.
 * 
 */
class MainMenu: public ScreenInteface{
    unsigned int width_;
    unsigned int height_;
    const ScreenManager& screen_manager_;
    FixedFramerate framerate;

    Draw::Texture::Manager& texture_manager_;
    Draw::Font::Manager& font_manager_;
    Synch::Loop& loop_synch_;

    Thread::Draw::Communication thread_comm_;

    std::shared_ptr<ScreenMaster::View> view_UI_;

    std::unique_ptr<Event::Manager> event_manager_;

    std::unique_ptr<Draw::Manager> draw_manager_;

    std::shared_ptr<Button::Exit> exit_button_;
    std::shared_ptr<Button::Default> sim_button_;
    std::shared_ptr<Tiles::Background> background_;

    void addButtons(std::shared_ptr<sf::RenderWindow> & window);
    void addBackground(std::shared_ptr<sf::RenderWindow> & window);
    void addOther();

    void endThreads(std::thread& thread);

public:
    MainMenu(const sf::Vector2u& viewSize, const ScreenManager& nextScreen);
    MainMenu(unsigned int width, unsigned int height, const ScreenManager& screenManager);
    ~MainMenu();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;

    virtual void init(std::shared_ptr<sf::RenderWindow> & window) override;

    virtual void release(std::shared_ptr<sf::RenderWindow> & window) override;

};


}




#endif