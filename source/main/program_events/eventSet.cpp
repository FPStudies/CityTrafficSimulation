#ifndef EVENT_SET_CPP
#define EVENT_SET_CPP

#include "eventSet.h"

EventSet::EventSet() {}

EventSet::~EventSet(){}

EventSet::EventSet(const EventSet& e)
{
    events.reserve(e.events.size());

    for(const auto& ev : e.events){
        events.push_back(std::move(std::unique_ptr<EventInterface>(ev->clone())));
    }
}

EventSet::EventSet(const EventInterface& event){
    events.push_back(std::move(std::unique_ptr<EventInterface>(event.clone())));
}

void EventSet::addEvent(const EventInterface& event){
    events.push_back(std::move(std::unique_ptr<EventInterface>(event.clone())));
}

bool EventSet::remove(const EventInterface& eventObject){
    for(auto it = events.begin(); it != events.end(); ++it){
        if((*it)->equals(eventObject)) {
            events.erase(it);
            return false;
        }
    }

    return true;
}


void EventSet::checkEventsOccurence(sf::Event& event, sf::RenderWindow& window){
    for(auto& ev : events){
        ev->run(window, event);
    }
}

bool EventSet::empty() const{
    return events.empty();
}

#endif