/*
 * Button.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "trigger/Button.h"

Trigger::Button::Button(std::shared_ptr<::Button::Interface>& button)
: button_(button)
{}

Trigger::Button::~Button() = default;

Trigger::Button::Button(Button&& other)
: button_(std::move(other.button_))
{}

Trigger::Button::Button(const Button& other)
: button_(other.button_)
{}

Trigger::Button& Trigger::Button::operator=(Button&& other){
    button_ = std::move(other.button_);
}

Trigger::Button* Trigger::Button::clone_impl() const{
    return new Trigger::Button(*this);
}

void Trigger::Button::trigger(sf::RenderWindow& window, std::unique_ptr<Control::KeyContainer>& control, const sf::Event& event) {
    if(button_->isButtonChoosed(sf::Mouse::getPosition(window))){
        // trigger functions

        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Mouse::Button::Left){
            button_->actionPressedButton();
        }
        else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Mouse::Button::Left){
            button_->actionReleasedButton();
        }
    }
}

std::unique_ptr<Trigger::Button> Trigger::Button::clone() const{
    return std::unique_ptr<Trigger::Button>(this->clone_impl());
}

bool Trigger::Button::equals(const Interface& other) const{
    if(typeid(other) == typeid(Trigger::Button) && button_ == dynamic_cast<const Button&>(other).button_)
        return true;
    return false;
}