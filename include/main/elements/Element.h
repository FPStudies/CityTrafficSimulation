/*
 * Element.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_ELEMENT_H
#define TRAFFIC_SIM_ELEMENT_H

#include <SFML/Graphics.hpp>
#include "../drawing/Drawable.h"
#include "../drawing/Texturing.h"

namespace Elements {

    using Texture = ::Drawing::Texture::Texture;
    using Texture_ptr = std::shared_ptr<Texture>;

    class Element: public sf::RectangleShape, public Drawable {
        
        Texture_ptr texture_;       
        sf::RenderStates states_;
        bool can_be_drawn_;

    public:
        
        Element (sf::Window& window, const Texture_ptr& texture);
        virtual ~Element();

        virtual void draw(sf::RenderTarget& target) const override;

        virtual sf::FloatRect getLocalBounds() const override;
        virtual sf::FloatRect getGlobalBounds() const override;
        virtual bool canBeDrawn() const override;
    };

}

#endif