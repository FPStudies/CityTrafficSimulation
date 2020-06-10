/*
 * Drag.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "event/Drag.h"

using namespace Trigger::Event;

Drag::Drag()
: was_pressed_(false)
{}

Drag::~Drag() = default;

Drag::Drag(Drag&& other)
: was_pressed_(other.was_pressed_)
{}

Drag::Drag(const Drag& other)
: was_pressed_(other.was_pressed_)
{}

Drag& Drag::operator=(Drag&& other){
    was_pressed_ = other.was_pressed_;
    return *this;
}

Drag* Drag::clone_impl() const{
    return new Drag(*this);
}

void Drag::trigger(sf::RenderWindow& window, const sf::Event& event) {
    /*if(this->isChoosedDefault(window, to_move_->)){
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
    }*/
}

std::unique_ptr<Drag> Drag::clone() const{
    return std::unique_ptr<Drag>(this->clone_impl());
}

bool Drag::equals(const Interface& other) const{
    if(typeid(other) == typeid(Drag)){
        const auto& it = dynamic_cast<const Drag&>(other);
        if(was_pressed_ == it.was_pressed_)
            return true;
    }
    return false;
}