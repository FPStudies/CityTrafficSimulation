/*
 * Control.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Control.h"

Event::Control::Control(std::unique_ptr<::Control::Mapping>& mapping)
: ctrlMapping_(std::move(mapping))
{}

Event::Control::~Control() = default;

Event::Control::Control(const Control& other)
: ctrlMapping_(std::make_unique<::Control::Mapping>(*other.ctrlMapping_))
{}

void Event::Control::run(sf::RenderWindow& window, const sf::Event& event){
    ctrlMapping_->trigger(window, event);
}

std::unique_ptr<Event::Control> Event::Control::clone() const{
    return std::make_unique<Control>(*this);
}

bool Event::Control::equals(const Interface& other) const{
    return typeid(other) == typeid(Control) &&
        dynamic_cast<const Control&>(other).ctrlMapping_ == this->ctrlMapping_;
}

::Control::Mapping& Event::Control::getMapping(){
    return *ctrlMapping_;
}

Event::Control* Event::Control::clone_impl() const{

return nullptr; //TODO:
}
