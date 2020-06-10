/*
 * ProgramSetup.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_RENDER_LOOP_CC
#define RAFFIC_SIM_RENDER_LOOP_CC

#include "ProgramSetup.h"


ProgramSetup::ProgramSetup(const unsigned int& width, const unsigned int& height, const char* name, const unsigned int& mode_bits_per_pixel)
: window_(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height, mode_bits_per_pixel), name)),
texture_manager_(Draw::Texture::Manager::getInstance()),
font_manager_(Draw::Font::Manager::getInstance()),
loop_synch_(Synch::Loop::create(1))
{}

ProgramSetup::~ProgramSetup() = default;

void ProgramSetup::setup(){
    texture_manager_.load("resource/texture/blue_light.jpg", "blue_light");
    texture_manager_.load("resource/texture/highway_road.jpg", "highway_road");
    texture_manager_.load("resource/texture/grey.jpg", "grey");
    font_manager_.load("resource/fonts/open-sans/OpenSans-Italic.ttf", "Normal");

    std::shared_ptr<StartScreen> start_screen = std::make_shared<StartScreen>();
    std::shared_ptr<ScreenMaster::Spec::MainMenu> main_menu = std::make_shared<ScreenMaster::Spec::MainMenu>(window_->getSize(), screen_manager_);
    std::shared_ptr<ScreenMaster::Spec::Simulation> simulation = std::make_shared<ScreenMaster::Spec::Simulation>(window_->getSize(), screen_manager_);
	screen_manager_.addScreen(start_screen, "StartScreen");
    screen_manager_.addScreen(main_menu, "MainMenu");
    screen_manager_.addScreen(simulation, "Simulation");

}

const int ProgramSetup::render(){
	screen_manager_.mainLoop(window_, "MainMenu");

    return EXIT_SUCCESS;
}




static const std::vector<sf::VideoMode> getFullscreenVideoModes() {
    return std::vector<sf::VideoMode>(sf::VideoMode::getFullscreenModes());
}

#endif
