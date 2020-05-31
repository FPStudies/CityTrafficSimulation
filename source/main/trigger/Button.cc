/*
 * Button.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "trigger/Button.h"

Trigger::Button::Button()
: button_(nullptr)
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

std::shared_ptr<Trigger::Button> Trigger::Button::create(){
    return std::make_shared<Trigger::Button>(Trigger::Button());
}

bool Trigger::Button::connect(std::shared_ptr<::Button::Interface>& button){
    if(button_) return true;
    button_ = button;
    button->setTrigger(shared_from_this());
}

void Trigger::Button::trigger(sf::RenderWindow& window, const sf::Event& event) {
    if(button_  && button_->isButtonChoosed(sf::Mouse::getPosition(window))){
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