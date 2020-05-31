/*
 * Basic.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_BASIC_EVENTS_CC
#define TRAFFIC_SIM_BASIC_EVENTS_CC

#include "BasicEvents.h"

Basic::Basic()
: EventInterface()
{}

Basic::~Basic(){}

Basic::Basic(const Basic& event) {};

void Basic::run(sf::RenderWindow& window, const sf::Event& event){
    if(event.type == sf::Event::Closed)
        window.close();
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
    
}

std::unique_ptr<Basic> Basic::clone() const{
    return std::unique_ptr<Basic>(this->clone_impl());
}

bool Basic::equals(const EventInterface& other) const{
    if(typeid(Basic) == typeid(other))
        return true;
    return false;
}

Basic* Basic::clone_impl() const{
    return new Basic(*this);
}

#endif