/*
 * Element.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_ELEMENT_H
#define TRAFFIC_SIM_ELEMENT_H

#include <SFML/Graphics.hpp>
#include "../../draw/Drawable.h"
#include "../../draw/Texturing.h"

namespace Element {

    using Texture = ::Draw::Texture::Texture;
    using Texture_ptr = std::shared_ptr<Texture>;

    class Element: public sf::RectangleShape, public Draw::Drawable {

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

        virtual void setPosition(const sf::Vector2f &position);
        virtual void setSize(const sf::Vector2f &size);
    };

}

#endif
