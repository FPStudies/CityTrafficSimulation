/*
 * Control.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Control.h"

Event::Control::Control(std::unique_ptr<::Control::Mapping>& mapping)
: ctrl_mapping_(std::move(mapping))
{}

Event::Control::Control()
: ctrl_mapping_(std::make_unique<::Control::Mapping>())
{}

Event::Control::~Control() = default;

Event::Control::Control(const Control& other)
: ctrl_mapping_(std::make_unique<::Control::Mapping>(*other.ctrl_mapping_))
{}

void Event::Control::run(sf::RenderWindow& window, const sf::Event& event){
    ctrl_mapping_->trigger(window, event);
}

std::unique_ptr<Event::Control> Event::Control::clone() const{
    return std::make_unique<Control>(*this);
}

bool Event::Control::equals(const Interface& other) const{
    return typeid(other) == typeid(Control) &&
        dynamic_cast<const Control&>(other).ctrl_mapping_ == this->ctrl_mapping_;
}

::Control::Mapping& Event::Control::getMapping(){
    return *ctrl_mapping_;
}

Event::Control* Event::Control::clone_impl() const{
    return new Event::Control(*this);
}
