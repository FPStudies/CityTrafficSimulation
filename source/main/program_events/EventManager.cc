/*
 * EventManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_EVENT_MANAGER_CC
#define TRAFFIC_SIM_EVENT_MANAGER_CC

#include "EventManager.h"
#include <iostream>

EventManager::EventSetInner::EventSetInner(const EventSet& event_set)
: event_set_(event_set), state_(EventManager::State::INACTIVE)
{}

EventManager::EventSetInner::EventSetInner(const EventSet& event_set, EventManager::State mode)
: event_set_(event_set), state_(mode)
{}

EventManager::EventSetInner::~EventSetInner() {}

EventManager::EventSetInner::EventSetInner(const EventSetInner& events)
: event_set_(events.event_set_), state_(events.state_)
{}

EventManager::EventSetInner::EventSetInner(const std::shared_ptr<EventInterface>& event)
: event_set_(EventSet(event)), state_(EventManager::State::INACTIVE)
{}

EventManager::EventSetInner::EventSetInner(const std::shared_ptr<EventInterface>& event, EventManager::State mode)
: event_set_(EventSet(event)), state_(mode)
{}

EventManager::EventManager() 
: events_sorted_(false), events_map_names_(), events_sorted_list_(), tmp_mode_(DEFAULT_HASH_MAP_SIZE)
{}

EventManager::~EventManager() {}

bool EventManager::EventSetInner::isActive() const{
    return state_ == EventManager::State::ACTIVE ? true : false;
}

EventSet& EventManager::EventSetInner::getEventSet() {
    return event_set_;
}

void EventManager::EventSetInner::setMode(EventManager::State mode){
    state_ = mode;
}

void EventManager::EventSetInner::addEventToSet(const std::shared_ptr<EventInterface>& event_object){
    event_set_.add(event_object);
}

bool EventManager::EventSetInner::removeEventFromSet(const std::shared_ptr<EventInterface>& event_object){
    return event_set_.remove(event_object);
}

bool EventManager::EventSetInner::empty() const{
    return event_set_.empty();
}

void EventManager::sortListBinaryVal(){
    auto begin = events_sorted_list_.begin(), end = --events_sorted_list_.end();

    while(begin != end){
        while(begin != end && (**begin).isActive()){
            ++begin;
        }

        while(begin != end && !(**end).isActive()){
            --end;
        }

        if(begin == end)
            break;
        // works on pointers
        auto tmp = (*begin);
        (*begin) = (*end);
        (*end) = tmp;
    }
}


void EventManager::changeMode(const std::string& name, EventManager::State mode){
    tmp_mode_[name] = mode;
    events_sorted_ = false;
}

void EventManager::runChangeMode(){
    for(auto it = tmp_mode_.cbegin(); it != tmp_mode_.cend(); ++it){
        auto val = events_map_names_.at(it->first);
        val->setMode(it->second);
    }
    tmp_mode_.clear();
}

void EventManager::add(const std::string& name, EventManager::State mode, const EventSet& event_object_set){
    Pointer tmp = Pointer(new EventSetInner(event_object_set, mode));
    events_map_names_[name] = tmp;
    events_sorted_list_.push_back(tmp);
    events_sorted_ = false;
}

bool EventManager::addNew(const std::string& name, EventManager::State mode, const EventSet& event_object_set){
    if(ifElementMapExist(name))
        return true;

    this->add(name, mode, event_object_set);
    return false;
}

void EventManager::addNewEventInterface(const std::string& name, EventManager::State mode, const std::shared_ptr<EventInterface>& event_object){
    Pointer tmp = Pointer(new EventSetInner(event_object, mode));
    events_map_names_[name] = tmp;
    events_sorted_list_.push_back(tmp);
    events_sorted_ = false;
}

void EventManager::add(const std::string& name, EventManager::State mode, const std::shared_ptr<EventInterface>& event_object){
    Map::iterator it;
    if(ifElementMapExist(name, it)){
        it->second->addEventToSet(event_object);
        it->second->setMode(mode);
        events_sorted_ = false;
    }
    else {
        addNewEventInterface(name, mode, event_object);
    }
}

bool EventManager::addNew(const std::string& name, EventManager::State mode, const std::shared_ptr<EventInterface>& event_object){
    Map::iterator it;
    if(ifElementMapExist(name, it))
        return true;
    addNewEventInterface(name, mode, event_object);

    return false;
}

bool EventManager::ifElementMapExist(const std::string& name, Map::iterator& it){
    if((it = events_map_names_.find(name)) == events_map_names_.end())
        return false;
    return true;
}

bool EventManager::ifElementMapExist(const std::string& name){
    if(events_map_names_.find(name) == events_map_names_.end())
        return false;
    return true;
}

bool EventManager::remove(const std::string& name){
    Map::iterator it;
    if(!ifElementMapExist(name, it))
        return true;

    for(List::iterator l = events_sorted_list_.begin(); l !=events_sorted_list_.end(); ++l){
        if(*l == it->second) {
            events_sorted_list_.erase(l);
            break;
        }
    }
    events_map_names_.erase(it);

    return false;
}

bool EventManager::remove(const std::string& name, const std::shared_ptr<EventInterface>& event_object){
    Map::iterator it;
    if(!ifElementMapExist(name, it))
        return true;

    for(List::iterator l = events_sorted_list_.begin(); l !=events_sorted_list_.end(); ++l){
        if(*l == it->second) {
            if((*l)->removeEventFromSet(event_object))
                return true;

            if((*l)->empty()){
                events_sorted_list_.erase(l);
                events_map_names_.erase(it);
            }
            break;
        }
    }

    return false;
}

void EventManager::checkEvents(sf::RenderWindow& window, sf::Event& event){
    if(!events_sorted_) {
        if(!tmp_mode_.empty())
            runChangeMode();
            
        sortListBinaryVal();
        events_sorted_ = true;
    }

    for(auto& it : events_sorted_list_){
        if(!it->isActive())
            break;

        it->getEventSet().checkEventsOccurence(event, window);
    }
}

#endif