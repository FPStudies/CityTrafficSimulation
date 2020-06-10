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
#include "../FixedFramerate.h"
#include "../ScreenManager.h"

#include "../../event/Manager.h"
#include "../../draw/Texturing.h"

#include "../View.h"

#include "../../synchronization/Loop.h"

#include "../event/Basic.h"

namespace ScreenMaster::Spec{

/**
 * @brief Screen that represent the simulation.
 * 
 */
class Simulation: public ScreenInteface{
    unsigned int width_;
    unsigned int height_;
    const ScreenManager& screen_manager_;
    FixedFramerate framerate;

    Draw::Texture::Manager& texture_manager_;
    Draw::Font::Manager& font_manager_;
    Synch::Loop& loop_synch_;

    std::shared_ptr<ScreenMaster::View> view_world_;
    std::shared_ptr<ScreenMaster::View> view_UI_;

    std::unique_ptr<b2World> world_;
    std::unique_ptr<Event::Manager> event_manager_;

    std::unique_ptr<Draw::Manager> draw_manager_;

    

public:

    Simulation(unsigned int width, unsigned int height, const ScreenManager& screenManager);
    Simulation(const sf::Vector2u& viewSize, const ScreenManager& screenManager);
    ~Simulation();

    ScreenID run(std::shared_ptr<sf::RenderWindow> & window) override;

    virtual void init(std::shared_ptr<sf::RenderWindow> & window) override;

    virtual void release(std::shared_ptr<sf::RenderWindow> & window) override;

};


}




#endif