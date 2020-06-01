/*
 * Button.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Button.h"

Trigger::Event::Button::Button()
: button_(nullptr)
{}

Trigger::Event::Button::~Button() = default;

Trigger::Event::Button::Button(Button&& other)
: button_(std::move(other.button_))
{}

Trigger::Event::Button::Button(const Button& other)
: button_(other.button_)
{}

Trigger::Event::Button& Trigger::Event::Button::operator=(Button&& other){
    button_ = std::move(other.button_);
    return *this;
}

Trigger::Event::Button* Trigger::Event::Button::clone_impl() const{
    return new Trigger::Event::Button(*this);
}

std::shared_ptr<Trigger::Event::Button> Trigger::Event::Button::create(){
    return std::make_shared<Trigger::Event::Button>(Trigger::Event::Button());
}

bool Trigger::Event::Button::connect(const std::shared_ptr<::Button::Interface>& button){
    if(button_) return true;
    button_ = button;
    button->addTrigger(shared_from_this());
    return false;
}

void Trigger::Event::Button::trigger(sf::RenderWindow& window, const sf::Event& event) {
    if(button_  && button_->isButtonChoosed(sf::Mouse::getPosition(window))){
        // trigger functions

        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){
            button_->actionPressedButton();
        }
        else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left){
            button_->actionReleasedButton();
        }
    }
}

std::unique_ptr<Trigger::Event::Button> Trigger::Event::Button::clone() const{
    return std::unique_ptr<Trigger::Event::Button>(this->clone_impl());
}

bool Trigger::Event::Button::equals(const Interface& other) const{
    if(typeid(other) == typeid(Trigger::Event::Button) && button_ == dynamic_cast<const Button&>(other).button_)
        return true;
    return false;
}