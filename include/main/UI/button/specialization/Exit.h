/*
 * Exit.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_SPECIALIZATION_EXIT_H
#define TRAFFIC_SIM_GAME_BUTTON_SPECIALIZATION_EXIT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Interface.h"
#include "../../../trigger/action/ExitWindow.h"
#include "../../../draw/Texturing.h"

namespace Button{
    class Exit: public ::Button::Interface, public sf::RectangleShape, public Draw::Drawable{
        using Texture = ::Draw::Texture::Texture;
        using Texture_ptr = std::shared_ptr<Texture>;

        Trigger::Action::ExitWindow exit_;

        Texture_ptr texture_;       
        sf::RenderStates states_;
        bool can_be_drawn;

    public:
        Exit(sf::Window& window, const Texture_ptr& texture);
        virtual ~Exit();
 
        virtual void draw(sf::RenderTarget& target) const override;
        virtual bool isButtonChoosed(sf::RenderWindow& window) override;

        virtual void actionPressedButton() override;
        virtual void actionReleasedButton() override;

        virtual sf::FloatRect getLocalBounds() const override;
        virtual sf::FloatRect getGlobalBounds() const override;
        virtual bool canBeDrawn() const override;
    };
}




#endif