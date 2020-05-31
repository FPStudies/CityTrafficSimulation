/*
 * Set.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Set.h"

using namespace Event;

Set::Set()
: SetTemplate<Interface>()
{}

Set::~Set(){}

Set::Set(const Set& e)
: SetTemplate<Interface>(e)
{}

Set::Set(const std::shared_ptr<Interface>& event)
: SetTemplate<Interface>(event)
{}



void Set::checkEventsOccurence(sf::Event& event, sf::RenderWindow& window){
    for(auto& ev : objects_){
        ev->run(window, event);
    }
}
