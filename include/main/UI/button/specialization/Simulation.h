/*
 * Simulation.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_SPECIALIZATION_SIMULATION_H
#define TRAFFIC_SIM_GAME_BUTTON_SPECIALIZATION_SIMULATION_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../../../trigger/action/ExitWindow.h"
#include "../../../draw/Texturing.h"
#include "../Interface.h"
#include "../../../screen/ScreenID.h"

namespace Button{
    
    // TODO, not to use 
    class Simulation: public InterfaceDrawTrans, public sf::RectangleShape{
        using Texture = ::Draw::Texture::Texture;
        using Texture_ptr = std::shared_ptr<Texture>;

        Trigger::Action::ExitWindow exit_;
        sf::Text text_;
        std::shared_ptr<Draw::Font::Font> font_;

        Texture_ptr texture_;       
        sf::RenderStates states_;
        bool can_be_drawn_;

        ScreenID next_screen_;
        bool is_next_screen_;

    public:
        Simulation(sf::Window& window, const Texture_ptr& texture, const ScreenID& nextScreen);
        virtual ~Simulation();
 
        virtual void draw(sf::RenderTarget& target) const override;
        virtual bool isButtonChoosed(sf::RenderWindow& window) override;

        virtual void actionPressedButton() override;
        virtual void actionReleasedButton() override;

        virtual sf::FloatRect getLocalBounds() const override;
        virtual sf::FloatRect getGlobalBounds() const override;
        virtual bool canBeDrawn() const override;

        void setFont(const std::shared_ptr<Draw::Font::Font>& font);
        void setPosition(const sf::Vector2f &position);
        void setSize(const sf::Vector2f &size);
        void setTextSize(unsigned int size);



    };
}




#endif