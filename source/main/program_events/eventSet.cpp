#ifndef EVENT_SET_CPP
#define EVENT_SET_CPP

#include "eventSet.h"

EventSet::EventSet()
: SetTemplate<EventInterface>()
{}

EventSet::~EventSet(){}

EventSet::EventSet(const EventSet& e)
: SetTemplate<EventInterface>(e)
{}

EventSet::EventSet(const std::shared_ptr<EventInterface>& event)
: SetTemplate<EventInterface>(event)
{}



void EventSet::checkEventsOccurence(sf::Event& event, sf::RenderWindow& window){
    for(auto& ev : objects){
        ev->run(window, event);
    }
}

#endif