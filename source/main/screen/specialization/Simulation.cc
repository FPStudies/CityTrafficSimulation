

#include "specialization/Simulation.h"

using namespace Screen::Spec;

Simulation::Simulation()
:texture_manager_(Draw::Texture::Manager::getInstance()),
font_manager_(Draw::Font::Manager::getInstance()),
loop_synch_(Synch::Loop::create(1))
{}

Simulation::~Simulation() = default;

ScreenID Simulation::run(std::shared_ptr<sf::RenderWindow> & window){
    return ScreenID();
}