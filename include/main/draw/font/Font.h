/*
 * Font.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_FONT_FONT_H
#define TRAFFIC_SIM_MAIN_DRAWING_FONT_FONT_H

#include <SFML/Graphics.hpp>

#include "../../utility/SharedResourceManager.hpp"



namespace Draw::Font{

/**
 * @brief A wrapper to the sf::Font. It inherit from SharedResource::Resource template.
 * 
 */
class Font: public ::SharedResource::Resource<sf::Font>{
    friend class Manager;

    Font(const std::string& path);
    Font(const sf::Font& font);

};

}

#endif
