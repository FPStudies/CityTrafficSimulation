/*
 * Manager.cc
 *
 *      Author: Kordowski Mateusz
 */

#include <iostream>

#include "Manager.h"

using namespace Event;

Manager::SetInner::SetInner(const Set& event_set)
: event_set_(event_set), state_(Manager::State::INACTIVE)
{}

Manager::SetInner::SetInner(const Set& event_set, Manager::State mode)
: event_set_(event_set), state_(mode)
{}

Manager::SetInner::~SetInner() {}

Manager::SetInner::SetInner(const SetInner& events)
: event_set_(events.event_set_), state_(events.state_)
{}

Manager::SetInner::SetInner(const std::shared_ptr<Interface>& event)
: event_set_(Set(event)), state_(Manager::State::INACTIVE)
{}

Manager::SetInner::SetInner(const std::shared_ptr<Interface>& event, Manager::State mode)
: event_set_(Set(event)), state_(mode)
{}

Manager::Manager(const std::shared_ptr<Screen::View>& view) 
: events_sorted_(false), events_map_names_(), events_sorted_list_(), tmp_mode_(), view_(view), mutex_modify_()
{}

Manager::~Manager() = default;

bool Manager::SetInner::isActive() const{
    return state_ == Manager::State::ACTIVE ? true : false;
}

Set& Manager::SetInner::getEventSet() {
    return event_set_;
}

void Manager::SetInner::setMode(Manager::State mode){
    state_ = mode;
}

void Manager::SetInner::addEventToSet(const std::shared_ptr<Interface>& event_object){
    event_set_.add(event_object);
}

bool Manager::SetInner::removeEventFromSet(const std::shared_ptr<Interface>& event_object){
    return event_set_.remove(event_object);
}

bool Manager::SetInner::empty() const{
    return event_set_.empty();
}

void Manager::sortListBinaryVal(){
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

    begin = enents_change_control_list_.begin(), end = --enents_change_control_list_.end();

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


bool Manager::changeMode(const std::string& name, Manager::State mode){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    auto val = events_map_names_.find(name);
    if(val == events_map_names_.end()){
        // it could be stored at other map
        val = enents_change_control_map_names_.find(name);
        if(val == enents_change_control_map_names_.end())
            return true;
    }
    tmp_mode_.push_back(MyPair(*(val->second), mode));
    events_sorted_ = false;
    
    return false;
}

void Manager::runChangeMode(){
    auto itEnd = tmp_mode_.end();
    for(auto it = tmp_mode_.begin(); it != itEnd; ++it){
        it->first.get().setMode(it->second);
    }
    tmp_mode_.clear();
}

bool Manager::isDifferentType(const Set& event_object_set){
    auto container = event_object_set.getAllConst();
    auto it = container.cbegin();
    auto itEnd = container.cend();
    auto prevType = (*(it++))->getType();
    for(; it != itEnd; ++it){
        if((*it)->getType() != prevType) return true;
    }
    return false;
}

bool Manager::addInner(const std::string& name, Manager::State mode, const Set& event_object_set){
    if(isDifferentType(event_object_set)) 
        return true;

    Pointer tmp = Pointer(new SetInner(event_object_set, mode));

    if(event_object_set.getAllConst().front()->getType() == Event::Interface::Type::Normal){
        events_map_names_[name] = tmp;
        events_sorted_list_.push_back(tmp);
    }
    else{
        enents_change_control_map_names_[name] = tmp;
        enents_change_control_list_.push_back(tmp);
    }
    events_sorted_ = false;

    return false;
}

bool Manager::add(const std::string& name, Manager::State mode, const Set& event_object_set){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    return this->addInner(name, mode, event_object_set);
}

bool Manager::addNew(const std::string& name, Manager::State mode, const Set& event_object_set){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    if(ifElementMapExist(name))
        return true;

    return this->addInner(name, mode, event_object_set);
}

void Manager::addNewEventInterface(const std::string& name, Manager::State mode, const std::shared_ptr<Interface>& event_object){
    Pointer tmp = Pointer(new SetInner(event_object, mode));

    if(event_object->getType() == Event::Interface::Type::Normal){
        events_map_names_[name] = tmp;
        events_sorted_list_.push_back(tmp);    
    }
    else{
        enents_change_control_map_names_[name] = tmp;
        enents_change_control_list_.push_back(tmp);
    }
    
    events_sorted_ = false;
}

bool Manager::add(const std::string& name, Manager::State mode, const std::shared_ptr<Interface>& event_object){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    Map::iterator it;
    if(ifElementMapExist(name, it)){
        if(it->second->getEventSet().getAllConst().front()->getType() != event_object->getType())
            return true;
            
        it->second->addEventToSet(event_object);
        it->second->setMode(mode);
        events_sorted_ = false;
    }
    else {
        addNewEventInterface(name, mode, event_object);
    }
    return false;
}

bool Manager::addNew(const std::string& name, Manager::State mode, const std::shared_ptr<Interface>& event_object){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    Map::iterator it;
    if(ifElementMapExist(name, it))
        return true;
    addNewEventInterface(name, mode, event_object);

    return false;
}

bool Manager::ifElementMapExist(const std::string& name, Map::iterator& it){
    if((it = events_map_names_.find(name)) == events_map_names_.end() || 
        (it = enents_change_control_map_names_.find(name)) == enents_change_control_map_names_.end())
        return false;
    return true;
}

bool Manager::ifElementMapExist(const std::string& name){
    if(events_map_names_.find(name) == events_map_names_.end() || 
        enents_change_control_map_names_.find(name) == enents_change_control_map_names_.end())
        return false;
    return true;
}

bool Manager::remove(const std::string& name){
    std::lock_guard<std::mutex> guard(mutex_modify_);
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

bool Manager::remove(const std::string& name, const std::shared_ptr<Interface>& event_object){
    std::lock_guard<std::mutex> guard(mutex_modify_);
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

void Manager::checkEvents(sf::RenderWindow& window, sf::Event& event){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    if(!events_sorted_) {
        if(!tmp_mode_.empty())
            runChangeMode();
            
        sortListBinaryVal();
        events_sorted_ = true;
    }

    window.setView(view_->getView());

    for(auto& it : events_sorted_list_){
        if(!it->isActive())
            break;

        it->getEventSet().checkEventsOccurence(event, window);
    }

    for(auto& it : enents_change_control_list_){
        if(!it->isActive())
            break;

        it->getEventSet().checkToggleOccurence(event, window, *this);
    }
}
