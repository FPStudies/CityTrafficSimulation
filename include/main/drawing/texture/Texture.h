/*
 * Texture.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_TEXTURE_H
#define TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_TEXTURE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../../utility/SharedResourceManager.hpp"

namespace Drawing::Texture{

class Texture: public ::SharedResource::Resource<sf::Texture>{
    friend class Manager;

    sf::IntRect portion_;
    bool request_for_deleting;

    Texture(const std::string& path, const sf::IntRect& area = sf::IntRect());
    Texture(const sf::Texture& texture, const sf::IntRect& area = sf::IntRect());

public:
    sf::IntRect& getRect();
    const sf::IntRect& getRect_const() const;
};

}

#endif
