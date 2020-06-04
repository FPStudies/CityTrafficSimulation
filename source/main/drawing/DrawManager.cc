/*
 * Manager.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Manager.h"
#include <iostream>

using namespace Draw;

const unsigned int Manager::DrawLayer::DEFAULT_LIST_SIZE = 50;

Manager::WindowCont Manager::windows_static_;

Manager::DrawLayer::DrawLayer(const std::string& name) 
: name_(name), container_(), render_(DEFAULT_LIST_SIZE)
{}

Manager::DrawLayer::~DrawLayer() = default;

bool Manager::DrawLayer::remove(std::shared_ptr<Drawable>& entity){
    ObjectPair::iterator it = container_.find(entity->getID());

    if(it != container_.end()){
        it->second = nullptr;
        container_.erase(it);
        return false;
    }
    return true;
}

void Manager::DrawLayer::clearNulls(){
    for(auto it = render_.begin(); it != render_.end();){
        if(it->get() == nullptr){
            it = render_.erase(it);
        }
        else{
            ++it;
        }
    }
}

void Manager::DrawLayer::add(std::shared_ptr<Drawable>& entity){
    container_[entity->getID()] = entity;
    render_.push_back(entity);
}

const std::string& Manager::DrawLayer::getName(){
    return name_;
}

void Manager::DrawLayer::setName(const std::string& name){
    this->name_ = name;
}

void Manager::DrawLayer::draw(sf::RenderTarget& target){
    for(auto it = render_.begin(); it != render_.end(); ++it){
        auto& sec = *it;
        if(sec && sec->canBeDrawn())
            sec->draw(target);
    }
}











bool Manager::addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity){ //check if reference or copy
    for(auto it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == layer_name){
            (*it)->add(entity);
            return false;
        }
    }
    return true;
}

void Manager::addFirstLayer(const std::string& layer_name){
    to_draw_.push_back(std::make_unique<DrawLayer>(layer_name));
}

bool Manager::addLayer(const std::string& previous_layer_name, const std::string& layer_name){
    for(auto it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == previous_layer_name){
            ++it;
            to_draw_.insert(it, std::make_unique<DrawLayer>(layer_name));
            return false;
        }
    }
    return true;
}

bool Manager::remove(const std::string& layer_name, std::shared_ptr<Drawable> entity){ //check if reference or copy
    auto it = to_draw_.begin();
    while(it != to_draw_.end()){
        if((*it)->getName() == layer_name){
            return (*it)->remove(entity);
        }
    }
    return true;
}

Manager::Manager(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window)
: to_draw_(), object_window_(window)
{
    addFirstLayer(layer_name);
}


Manager::~Manager() {}

Manager::Manager(Manager&& other) noexcept
: to_draw_(std::move(other.to_draw_)), object_window_(std::move(other.object_window_))
{}

std::unique_ptr<Manager> Manager::create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window){
    for(WindowCont::const_iterator it = windows_static_.cbegin(); it != windows_static_.cend(); ++it){
        if(it->lock() == window) 
            throw std::invalid_argument("This window is already in some Manager instance.");
    }
    Manager* draw_ptr = new Manager(layer_name, window);
    return std::move(std::unique_ptr<Manager>(draw_ptr));
}

void Manager::drawAll(){
    for(auto& it : to_draw_){
        it->draw(*object_window_);
    }
}

bool Manager::drawLayer(const std::string& layer_name){
    auto it = to_draw_.begin();
    while(it != to_draw_.end()){
        if((*it)->getName() == layer_name){
            (*it)->draw(*object_window_);
            return false;
        }
        ++it;
    }
    return true;
}

void Manager::clearNulls(){
    for(auto& it : to_draw_){
        it->clearNulls();
    }
}

void Manager::clearNulls(const std::string& layer_name){
    for(auto& it : to_draw_){
        if(it->getName() == layer_name){
            it->clearNulls();
            break;
        }
    }
}