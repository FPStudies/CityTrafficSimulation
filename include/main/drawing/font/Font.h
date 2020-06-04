/*
 * Font.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_FONT_FONT_H
#define TRAFFIC_SIM_MAIN_DRAWING_FONT_FONT_H

#include <SFML/Graphics.hpp>

#include "../../utility/SharedResourceManager.hpp"



namespace Drawing::Font{


class Font: public ::SharedResource::Resource<sf::Font>{
    friend class Manager;

    Font(const std::string& path);
    Font(const sf::Font& font);

public:
    sf::Font& getFont();

    const sf::Font& getFont_const() const;
};

}

#endif
