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

#include "main/event/Manager.h"
#include "main/event/Basic.h"
#include "../include/main/screen/ScreenManager.h"
#include "../include/main/screen/StartScreen.h"
#include "../include/main/screen/specialization/MainMenu.h"
#include "../include/main/screen/specialization/Simulation.h"

#include "main/draw/Texturing.h"
#include "main/synchronization/Loop.h"

/**
 * @brief A class used to create screen and other common objects used in this project.
 * 
 */
class ProgramSetup{
    std::shared_ptr<sf::RenderWindow> window_;

    Draw::Texture::Manager& texture_manager_;
    Draw::Font::Manager& font_manager_;
    Synch::Loop& loop_synch_;

    ScreenManager screen_manager_;
    
public:
    ProgramSetup(const unsigned int& width, const unsigned int& height, const char* name, const unsigned int& mode_bits_per_pixel = 32);
    ~ProgramSetup();

    /**
     * @brief Start the main program loop.
     * 
     * @return const int 0 if no errors. It uses a defines in SFML/Graphics.hpp started with "EXIT_"
     */
    const int render();
    
    void setup();


    /** 
     * @return const std::vector<sf::VideoMode>& - avaliable resolutions and pixel depth mode (in bits per pixels)
     */
    static const std::vector<sf::VideoMode> getFullscreenVideoModes();
};

#endif
