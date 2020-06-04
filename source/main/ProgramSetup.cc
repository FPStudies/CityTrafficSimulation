/*
 * ProgramSetup.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_RENDER_LOOP_CC
#define RAFFIC_SIM_RENDER_LOOP_CC

#include "ProgramSetup.h"

using namespace sf;

ProgramSetup::ProgramSetup(const unsigned int& width, const unsigned int& height, const char* name, const unsigned int& mode_bits_per_pixel)
: window_(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height, mode_bits_per_pixel), name))
{}

ProgramSetup::~ProgramSetup(){}

const int ProgramSetup::render(){

    ScreenManager screen_manager;
	std::shared_ptr<StartScreen> start_screen = std::make_shared<StartScreen>();
	screen_manager.addScreen(start_screen, "startScreen");
    sf::Window tmp;

	screen_manager.mainLoop(window_, *start_screen);


    return EXIT_SUCCESS;
}




static const std::vector<sf::VideoMode> getFullscreenVideoModes() {
    return std::vector<sf::VideoMode>(sf::VideoMode::getFullscreenModes());
}

#endif
