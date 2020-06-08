/*
 * Simulation.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_SPECIALIZATION_SIMULATION_H
#define TRAFFIC_SIM_MAIN_SCREEN_SPECIALIZATION_SIMULATION_H

#include <Box2D/Box2D.h>
#include <memory>

#include "../ScreenInterface.h"

#include "../../event/Manager.h"
#include "../../draw/Texturing.h"

#include "../View.h"

#include "../../synchronization/Loop.h"
#include "../Loopback.h"

namespace Screen::Spec{

class Simulation: public ScreenInteface{
    Draw::Texture::Manager& texture_manager_;
    Draw::Font::Manager& font_manager_;
    Synch::Loop& loop_synch_;

    std::shared_ptr<Screen::View> view_world_;
    std::shared_ptr<Screen::View> view_UI_;

    std::unique_ptr<b2World> world_;
    std::unique_ptr<Event::Manager> event_manager_;

    std::unique_ptr<Draw::Manager> draw_manager_;

public:
    Simulation();
    ~Simulation();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;


};


}




#endif