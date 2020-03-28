#ifndef DRAW_MANAGER_CPP
#define DRAW_MANAGER_CPP

#include "drawManager.h"

DrawManager::WindowCont DrawManager::windowsStatic;

void DrawManager::add(std::shared_ptr<Drawable> entity){
    toDraw[entity->getID()] = entity;
}

void DrawManager::remove(std::shared_ptr<Drawable> entity){
    toDraw.erase(entity->getID());
}

DrawManager::DrawManager(std::shared_ptr<sf::RenderWindow>& window)
: toDraw()
{}
DrawManager::~DrawManager() {}

DrawManager::DrawManager(const DrawManager&& other)
: toDraw(std::move(other.toDraw)), objectWindow(std::move(other.objectWindow))
{}

DrawManager DrawManager::create(std::shared_ptr<sf::RenderWindow>& window){
    for(WindowCont::const_iterator it = windowsStatic.cbegin(); it != windowsStatic.cend(); ++it){
        if(it->lock() == window) throw std::invalid_argument("This window is already in some DrawManager instance.");
    }
    return std::move(DrawManager(window));
}

void DrawManager::drawAll(){
    for(auto& it : toDraw){
        it.second->draw();
    }
}

#endif