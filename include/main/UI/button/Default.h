/*
 * Default.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_DEFAULT_H
#define TRAFFIC_SIM_GAME_BUTTON_DEFAULT_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../trigger/action/Interface.h"
#include "../../draw/Texturing.h"
#include "Interface.h"

namespace Button{


class Default: public InterfaceDrawTrans, public sf::RectangleShape{
    using Texture = ::Draw::Texture::Texture;
    using Texture_ptr = std::shared_ptr<Texture>;

    std::vector<std::shared_ptr<Trigger::Action::Interface>> action_triggers_pressed_;
    std::vector<std::shared_ptr<Trigger::Action::Interface>> action_triggers_released_;

    sf::Text text_;
    std::shared_ptr<Draw::Font::Font> font_;

    Texture_ptr texture_;       
    sf::RenderStates states_;
    bool can_be_drawn_;

public:
    Default(sf::Window& window, const Texture_ptr& texture);
    virtual ~Default();

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

    Draw::Font::Font& getFont();
    sf::Text& getText();

    void addTriggerOnPressed(const std::shared_ptr<Trigger::Action::Interface>& trigger);
    void addTriggerOnReleased(const std::shared_ptr<Trigger::Action::Interface>& trigger);

};

}




#endif