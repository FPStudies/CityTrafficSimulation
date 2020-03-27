#ifndef EVENT_MANAGER_CPP
#define EVENT_MANAGER_CPP

#include "eventManager.h"
#include <iostream>

EventManager::EventSetInner::EventSetInner(const EventSet& eventSet)
: eventSet(eventSet), state(EventManager::State::Inactive)
{}

EventManager::EventSetInner::EventSetInner(const EventSet& eventSet, EventManager::State mode)
: eventSet(eventSet), state(mode)
{}

EventManager::EventSetInner::~EventSetInner() {}

EventManager::EventSetInner::EventSetInner(const EventSetInner& events)
: eventSet(events.eventSet), state(events.state)
{}

EventManager::EventSetInner::EventSetInner(const EventInterface& event)
: eventSet(EventSet(event)), state(EventManager::State::Inactive)
{}

EventManager::EventSetInner::EventSetInner(const EventInterface& event, EventManager::State mode)
: eventSet(EventSet(event)), state(mode)
{}

EventManager::EventManager() 
: eventsSorted(false)
{}

EventManager::~EventManager() {}

bool EventManager::EventSetInner::isActive() const{
    return state == EventManager::State::Active ? true : false;
}

EventSet& EventManager::EventSetInner::getEventSet() {
    return eventSet;
}

void EventManager::EventSetInner::setMode(EventManager::State mode){
    state = mode;
}

void EventManager::EventSetInner::addEventToSet(const EventInterface& eventObject){
    eventSet.addEvent(eventObject);
}

bool EventManager::EventSetInner::removeEventFromSet(const EventInterface& eventObject){
    return eventSet.remove(eventObject);
}

bool EventManager::EventSetInner::empty() const{
    return eventSet.empty();
}

void EventManager::sortListBinaryVal(){
    auto begin = eventsSortedList.begin(), end = --eventsSortedList.end();

    while(begin != end){
        while(begin != end && (**begin).isActive()){
            ++begin;
        }

        while(begin != end && !(**end).isActive()){
            --end;
        }

        if(begin == end) break;
        // works on pointers
        auto tmp = (*begin);
        (*begin) = (*end);
        (*end) = tmp;
    }
}


void EventManager::changeMode(const std::string& name, EventManager::State mode){
    auto val = eventsMapNames.at(name);
    val->setMode(mode);
    eventsSorted = false;
}

void EventManager::add(const std::string& name, EventManager::State mode, const EventSet& eventObjectSet){
    Pointer tmp = Pointer(new EventSetInner(eventObjectSet, mode));
    eventsMapNames[name] = tmp;
    eventsSortedList.push_back(tmp);
    eventsSorted = false;
}

bool EventManager::addNew(const std::string& name, EventManager::State mode, const EventSet& eventObjectSet){
    if(ifElementMapExist(name)) return true;

    this->add(name, mode, eventObjectSet);
    return false;
}

void EventManager::addNewEventInterface(const std::string& name, EventManager::State mode, const EventInterface& eventObject){
    Pointer tmp = Pointer(new EventSetInner(eventObject, mode));
    eventsMapNames[name] = tmp;
    eventsSortedList.push_back(tmp);
    eventsSorted = false;
}

void EventManager::add(const std::string& name, EventManager::State mode, const EventInterface& eventObject){
    Map::iterator it;
    if(ifElementMapExist(name, it)){
        it->second->addEventToSet(eventObject);
        it->second->setMode(mode);
        eventsSorted = false;
    }
    else {
        addNewEventInterface(name, mode, eventObject);
    }
}

bool EventManager::addNew(const std::string& name, EventManager::State mode, const EventInterface& eventObject){
    Map::iterator it;
    if(ifElementMapExist(name, it)) return true;
    addNewEventInterface(name, mode, eventObject);

    return false;
}

bool EventManager::ifElementMapExist(const std::string& name, Map::iterator& it){
    if((it = eventsMapNames.find(name)) == eventsMapNames.end()) return false;
    return true;
}

bool EventManager::ifElementMapExist(const std::string& name){
    if(eventsMapNames.find(name) == eventsMapNames.end()) return false;
    return true;
}

bool EventManager::remove(const std::string& name){
    Map::iterator it;
    if(ifElementMapExist(name, it)) return true;

    for(List::iterator l = eventsSortedList.begin(); l !=eventsSortedList.end(); ++l){
        if(*l == it->second) {
            eventsSortedList.erase(l);
            break;
        }
    }
    eventsMapNames.erase(it);

    return false;
}

bool EventManager::remove(const std::string& name, const EventInterface& eventObject){
    Map::iterator it;
    if(ifElementMapExist(name, it)) return true;

    for(List::iterator l = eventsSortedList.begin(); l !=eventsSortedList.end(); ++l){
        if(*l == it->second) {
            if((*l)->removeEventFromSet(eventObject)) return true;

            if((*l)->empty()){
                eventsSortedList.erase(l);
                eventsMapNames.erase(it);
            }
            break;
        }
    }

    return false;
}

void EventManager::checkEvents(sf::RenderWindow& window, sf::Event& event){
    if(!eventsSorted) {
        sortListBinaryVal();
        eventsSorted = true;
    }

    for(auto& it : eventsSortedList){
        if(!it->isActive()) break;

        it->getEventSet().checkEventsOccurence(event, window);
    }
}

#endif