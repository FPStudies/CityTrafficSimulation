/*
 * Background.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UI_TILES_BACKGROUND_H
#define TRAFFIC_SIM_MAIN_UI_TILES_BACKGROUND_H

#include <SFML/Graphics.hpp>
#include "../../draw/Drawable.h"
#include "../../draw/Texturing.h"

namespace Tiles {

class Background: public Draw::Drawable, public sf::RectangleShape {
    using Texture = ::Draw::Texture::Texture;
    using Texture_ptr = std::shared_ptr<Texture>;
    
    Texture_ptr texture_;    
    sf::RenderStates states_;   
    bool can_be_drawn_;

public:
    
    Background(const Texture_ptr& texture);
    virtual ~Background();

    virtual void draw(sf::RenderTarget& target) const override;

    virtual sf::FloatRect getLocalBounds() const override;
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual bool canBeDrawn() const override;
};

}

#endif