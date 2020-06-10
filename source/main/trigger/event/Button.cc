/*
 * Button.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "event/Button.h"

Trigger::Event::Button::Button()
: button_(nullptr), was_pressed_(false)
{}

Trigger::Event::Button::~Button() = default;

Trigger::Event::Button::Button(Button&& other)
: button_(std::move(other.button_)), was_pressed_(other.was_pressed_)
{}

Trigger::Event::Button::Button(const Button& other)
: button_(other.button_), was_pressed_(other.was_pressed_)
{}

Trigger::Event::Button& Trigger::Event::Button::operator=(Button&& other){
    button_ = std::move(other.button_);
    was_pressed_ = other.was_pressed_;
    return *this;
}

Trigger::Event::Button* Trigger::Event::Button::clone_impl() const{
    return new Trigger::Event::Button(*this);
}

std::shared_ptr<Trigger::Event::Button> Trigger::Event::Button::create(){
    return std::make_shared<Trigger::Event::Button>(Trigger::Event::Button());
}

bool Trigger::Event::Button::connectWith(const std::shared_ptr<::Button::Interface>& button){
    if(button_) return true;
    button_ = button;
    return false;
}

bool Trigger::Event::Button::connect(const std::shared_ptr<::Button::Interface>& button, const std::shared_ptr<Trigger::Event::Button>& thisTrigger){
    if(thisTrigger->connectWith(button)) return true;
    ::Button::BridgeFromTriggerToInterface::connectTriggerToInterface(button, thisTrigger);
    return false;
}

void Trigger::Event::Button::trigger(sf::RenderWindow& window, const sf::Event& event) {
    if(button_  && button_->isButtonChoosed(window)){
        // trigger functions
        
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Left){
            was_pressed_ = true;
            button_->actionPressedButton();
        }
        else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left && was_pressed_){
            button_->actionReleasedButton();
            was_pressed_ = false;
        }
    }
    else{
        was_pressed_ = false;
    }
}

std::unique_ptr<Trigger::Event::Button> Trigger::Event::Button::clone() const{
    return std::unique_ptr<Trigger::Event::Button>(this->clone_impl());
}

bool Trigger::Event::Button::equals(const Interface& other) const{
    if(typeid(other) == typeid(Trigger::Event::Button)){
        const auto& it = dynamic_cast<const Button&>(other);
        if(button_ == it.button_ && was_pressed_ == it.was_pressed_)
            return true;
    }
    return false;
}