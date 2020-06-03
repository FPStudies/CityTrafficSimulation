/*
 * DrawManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "DrawManager.h"

const unsigned int DrawManager::DrawLayer::DEFAULT_LIST_SIZE = 50;

DrawManager::WindowCont DrawManager::windows_static_;

DrawManager::DrawLayer::DrawLayer(const std::string& name) 
: name_(name), container_(), render_(DEFAULT_LIST_SIZE)
{}

DrawManager::DrawLayer::~DrawLayer() = default;

bool DrawManager::DrawLayer::remove(std::shared_ptr<Drawable>& entity){
    ObjectPair::iterator it = container_.find(entity->getID());

    if(it != container_.end()){
        it->second = nullptr;
        container_.erase(it);
        return false;
    }
    return true;
}

void DrawManager::DrawLayer::clearNulls(){
    for(auto it = render_.begin(); it != render_.end();){
        if(it->get() == nullptr){
            it = render_.erase(it);
        }
        else{
            ++it;
        }
    }
}

void DrawManager::DrawLayer::add(std::shared_ptr<Drawable>& entity){
    container_[entity->getID()] = entity;
    render_.push_back(entity);
}

const std::string& DrawManager::DrawLayer::getName(){
    return name_;
}

void DrawManager::DrawLayer::setName(const std::string& name){
    this->name_ = name;
}

void DrawManager::DrawLayer::draw(sf::RenderTarget& target){
    for(auto it = render_.begin(); it != render_.end(); ++it){
        auto& sec = *it;
        if(sec && sec->canBeDrawn())
            sec->draw(target);
    }
}











bool DrawManager::addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity){ //check if reference or copy
    for(auto it = to_draw_.begin(); it != to_draw_.end(); ++it){
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
    for(auto it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == previous_layer_name){
            ++it;
            to_draw_.insert(it, std::make_unique<DrawLayer>(layer_name));
            return false;
        }
    }
    return true;
}

bool DrawManager::remove(const std::string& layer_name, std::shared_ptr<Drawable> entity){ //check if reference or copy
    auto it = to_draw_.begin();
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

std::unique_ptr<DrawManager> DrawManager::create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window){
    for(WindowCont::const_iterator it = windows_static_.cbegin(); it != windows_static_.cend(); ++it){
        if(it->lock() == window) 
            throw std::invalid_argument("This window is already in some DrawManager instance.");
    }
    DrawManager* draw_ptr = new DrawManager(layer_name, window);
    return std::move(std::unique_ptr<DrawManager>(draw_ptr));
}

void DrawManager::drawAll(){
    auto it = to_draw_.begin();
    while(it != to_draw_.end()){
        (*it)->draw(*object_window_);
    }
}

bool DrawManager::drawLayer(const std::string& layer_name){
    auto it = to_draw_.begin();
    while(it != to_draw_.end()){
        if((*it)->getName() == layer_name){
            (*it)->draw(*object_window_);
            return false;
        }
    }
    return true;
}

void DrawManager::clearNulls(){
    for(auto& it : to_draw_){
        it->clearNulls();
    }
}

void DrawManager::clearNulls(const std::string& layer_name){
    for(auto& it : to_draw_){
        if(it->getName() == layer_name){
            it->clearNulls();
            break;
        }
    }
}