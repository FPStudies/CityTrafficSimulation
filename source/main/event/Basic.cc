/*
 * Basic.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Basic.h"

using namespace Event;

Basic::Basic()
: Interface()
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

bool Basic::equals(const Interface& other) const{
    if(typeid(Basic) == typeid(other))
        return true;
    return false;
}

Basic* Basic::clone_impl() const{
    return new Basic(*this);
}
