#ifndef DRAW_MANAGER_CPP
#define DRAW_MANAGER_CPP

#include "drawManager.h"

DrawManager::WindowCont DrawManager::windowsStatic;

DrawManager::DrawLayer::DrawLayer(const std::string& name) 
: name(name), container()
{}

DrawManager::DrawLayer::~DrawLayer() {}

DrawManager::ObjectPair& DrawManager::DrawLayer::getContainer(){
    return container;
}

bool DrawManager::DrawLayer::remove(std::shared_ptr<Drawable>& entity){
    ObjectPair::iterator it = container.find(entity->getID());

    if(it != container.end()){
        container.erase(it);
        return false;
    }
    return true;
}

void DrawManager::DrawLayer::add(std::shared_ptr<Drawable>& entity){
    container[entity->getID()] = entity;
}

const std::string& DrawManager::DrawLayer::getName(){
    return name;
}

void DrawManager::DrawLayer::setName(const std::string& name){
    this->name = name;
}

void DrawManager::DrawLayer::draw(){
    for(auto it = container.begin(); it != container.end(); ++it){
        it->second->draw();
    }
}











bool DrawManager::addEntity(const std::string& layerName, std::shared_ptr<Drawable> entity){
    for(List::iterator it = toDraw.begin(); it != toDraw.end(); ++it){
        if((*it)->getName() == layerName){
            (*it)->add(entity);
            return false;
        }
    }
    return true;
}

void DrawManager::addFirstLayer(const std::string& layerName){
    toDraw.push_back(std::make_unique<DrawLayer>(layerName));
}

bool DrawManager::addLayer(const std::string& previousLayerName, const std::string& layerName){
    for(List::iterator it = toDraw.begin(); it != toDraw.end(); ++it){
        if((*it)->getName() == previousLayerName){
            ++it;
            toDraw.insert(it, std::make_unique<DrawLayer>(layerName));
            return false;
        }
    }
    return true;
}

bool DrawManager::remove(const std::string& layerName, std::shared_ptr<Drawable> entity){
    List::iterator it = toDraw.begin();
    while(it != toDraw.end()){
        if((*it)->getName() == layerName){
            return (*it)->remove(entity);
        }
    }
    return true;
}

DrawManager::DrawManager(const std::string& layerName, std::shared_ptr<sf::RenderWindow>& window)
: toDraw(), objectWindow(window)
{
    addFirstLayer(layerName);
}


DrawManager::~DrawManager() {}

DrawManager::DrawManager(DrawManager&& other) noexcept
: toDraw(std::move(other.toDraw)), objectWindow(std::move(other.objectWindow))
{}

DrawManager DrawManager::create(const std::string& layerName, std::shared_ptr<sf::RenderWindow>& window){
    for(WindowCont::const_iterator it = windowsStatic.cbegin(); it != windowsStatic.cend(); ++it){
        if(it->lock() == window) throw std::invalid_argument("This window is already in some DrawManager instance.");
    }
    return std::move(DrawManager(layerName, window));
}

void DrawManager::drawAll(){
    List::iterator it = toDraw.begin();
    while(it != toDraw.end()){
        (*it)->draw();
    }
}

bool DrawManager::drawLayer(const std::string& layerName){
    List::iterator it = toDraw.begin();
    while(it != toDraw.end()){
        if((*it)->getName() == layerName){
            (*it)->draw();
            return false;
        }
    }
    return true;
}

#endif