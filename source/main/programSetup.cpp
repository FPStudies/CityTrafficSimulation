#ifndef ZPR_TRAFFIC_SIM_RENDER_LOOP_CPP
#define ZPR_TRAFFIC_SIM_RENDER_LOOP_CPP

#include "programSetup.h"

using namespace sf;

ProgramSetup::ProgramSetup(const unsigned int& width, const unsigned int& height, const char* name, const unsigned int& modeBitsPerPixel)
: window(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height, modeBitsPerPixel), name))
{}

ProgramSetup::~ProgramSetup(){}

const int ProgramSetup::render(){

    ScreenManager screenManager;
	std::shared_ptr<StartScreen> startScreen = std::make_shared<StartScreen>();
	screenManager.addScreen(startScreen, "startScreen");

	screenManager.mainLoop(window, *startScreen);


    return EXIT_SUCCESS;
}




static const std::vector<sf::VideoMode> getFullscreenVideoModes() {
    return std::vector<sf::VideoMode>(sf::VideoMode::getFullscreenModes());
}

#endif
