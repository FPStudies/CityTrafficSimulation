/*
 * ProgramSetup.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_RENDER_LOOP_H
#define TRAFFIC_SIM_RENDER_LOOP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "main/program_events/EventManager.h"
#include "main/program_events/BasicEvents.h"
#include "../include/main/screen/ScreenManager.h"
#include "../include/main/screen/StartScreen.h"


class ProgramSetup{
    std::shared_ptr<sf::RenderWindow> window_;
    
public:
    ProgramSetup(const unsigned int& width, const unsigned int& height, const char* name, const unsigned int& mode_bits_per_pixel = 32);
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
