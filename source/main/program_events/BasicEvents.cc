/*
 * BasicEvents.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_BASIC_EVENTS_CC
#define TRAFFIC_SIM_BASIC_EVENTS_CC

#include "BasicEvents.h"

BasicEvents::BasicEvents()
: EventInterface()
{}

BasicEvents::~BasicEvents(){}

BasicEvents::BasicEvents(const BasicEvents& event) {};

void BasicEvents::run(sf::RenderWindow& window, sf::Event& event){
    if(event.type == sf::Event::Closed)
        window.close();
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
    
}

std::unique_ptr<BasicEvents> BasicEvents::clone() const{
    return std::unique_ptr<BasicEvents>(this->clone_impl());
}

bool BasicEvents::equals(const EventInterface& other) const{
    if(typeid(BasicEvents) == typeid(other))
        return true;
    return false;
}

BasicEvents* BasicEvents::clone_impl() const{
    return new BasicEvents(*this);
}

#endif