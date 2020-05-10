/*
 * DrawManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAW_MANAGER_CC
#define TRAFFIC_SIM_DRAW_MANAGER_CC

#include "DrawManager.h"

DrawManager::WindowCont DrawManager::windows_static_;

DrawManager::DrawLayer::DrawLayer(const std::string& name) 
: name_(name), container_()
{}

DrawManager::DrawLayer::~DrawLayer() {}

DrawManager::ObjectPair& DrawManager::DrawLayer::getContainer(){
    return container_;
}

bool DrawManager::DrawLayer::remove(std::shared_ptr<Drawable>& entity){
    ObjectPair::iterator it = container_.find(entity->getID());

    if(it != container_.end()){
        container_.erase(it);
        return false;
    }
    return true;
}

void DrawManager::DrawLayer::add(std::shared_ptr<Drawable>& entity){
    container_[entity->getID()] = entity;
}

const std::string& DrawManager::DrawLayer::getName(){
    return name_;
}

void DrawManager::DrawLayer::setName(const std::string& name){
    this->name_ = name;
}

void DrawManager::DrawLayer::draw(){
    for(auto it = container_.begin(); it != container_.end(); ++it){
        it->second->draw();
    }
}











bool DrawManager::addEntity(const std::string& layer_name, std::shared_ptr<Drawable>& entity){ //check if reference or copy
    for(List::iterator it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == layer_name){
            (*it)->add(entity);
            return false;
        }
    }
    return true;
}

void DrawManager::addFirstLayer(const std::string& layer_name){
    to_draw_.push_back(std::make_unique<DrawLayer>(layer_name));
}

bool DrawManager::addLayer(const std::string& previous_layer_name, const std::string& layer_name){
    for(List::iterator it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == previous_layer_name){
            ++it;
            to_draw_.insert(it, std::make_unique<DrawLayer>(layer_name));
            return false;
        }
    }
    return true;
}

bool DrawManager::remove(const std::string& layer_name, std::shared_ptr<Drawable>& entity){ //check if reference or copy
    List::iterator it = to_draw_.begin();
    while(it != to_draw_.end()){
        if((*it)->getName() == layer_name){
            return (*it)->remove(entity);
        }
    }
    return true;
}

DrawManager::DrawManager(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window)
: to_draw_(), object_window_(window)
{
    addFirstLayer(layer_name);
}


DrawManager::~DrawManager() {}

DrawManager::DrawManager(DrawManager&& other) noexcept
: to_draw_(std::move(other.to_draw_)), object_window_(std::move(other.object_window_))
{}

DrawManager DrawManager::create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window){
    for(WindowCont::const_iterator it = windows_static_.cbegin(); it != windows_static_.cend(); ++it){
        if(it->lock() == window) 
            throw std::invalid_argument("This window is already in some DrawManager instance.");
    }
    return std::move(DrawManager(layer_name, window));
}

void DrawManager::drawAll(){
    List::iterator it = to_draw_.begin();
    while(it != to_draw_.end()){
        (*it)->draw();
    }
}

bool DrawManager::drawLayer(const std::string& layer_name){
    List::iterator it = to_draw_.begin();
    while(it != to_draw_.end()){
        if((*it)->getName() == layer_name){
            (*it)->draw();
            return false;
        }
    }
    return true;
}

#endif
