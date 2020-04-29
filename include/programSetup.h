#ifndef ZPR_TRAFFIC_SIM_RENDER_LOOP_H
#define ZPR_TRAFFIC_SIM_RENDER_LOOP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "main/program_events/eventManager.h"
#include "main/program_events/basicEvents.h"
#include "../include/main/screen/screenManager.h"
#include "../include/main/screen/startScreen.h"


class ProgramSetup{
    std::shared_ptr<sf::RenderWindow> window;
    
public:
    ProgramSetup(const unsigned int& width, const unsigned int& height, const char* name, const unsigned int& modeBitsPerPixel = 32);
    ~ProgramSetup();

    /**
     * @brief Start the main program loop.
     * 
     * @return const int 0 if no errors. It uses a defines in SFML/Graphics.hpp started with "EXIT_"
     */
    const int render();


    /** 
     * @return const std::vector<sf::VideoMode>& - avaliable resolutions and pixel depth mode (in bits per pixels)
     */
    static const std::vector<sf::VideoMode> getFullscreenVideoModes();
};

#endif