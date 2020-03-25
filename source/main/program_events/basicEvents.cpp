#ifndef BASIC_EVENTS_CPP
#define BASIC_EVENTS_CPP

#include "basicEvents.h"

BasicEvents::BasicEvents(){}

BasicEvents::~BasicEvents(){}

BasicEvents::BasicEvents(const BasicEvents& event) {};

void BasicEvents::run(sf::RenderWindow& window, sf::Event& event){
    if(event.type == sf::Event::Closed) window.close();
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
    
}

EventInterface* BasicEvents::clone() const{
    return new BasicEvents(*this);
}

bool BasicEvents::equals(const EventInterface& other) const{
    if(typeid(BasicEvents) == typeid(other)) return true;
    return false;
}

#endif