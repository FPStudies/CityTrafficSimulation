#ifndef SCREEN_MANAGER_CPP
#define SCREEN_MANAGER_CPP

#include "screenManager.h"

ScreenManager::ScreenManager() {}

ScreenManager::~ScreenManager() {}

ScreenManager::Pair::Pair(const ScreenID& ID, const std::string& name, const std::shared_ptr<ScreenInteface>& screen)
: ID(ID), name(name), screen(screen)
{}

ScreenManager::Pair::Pair(const Pair& other)
: ID(other.ID), name(other.name), screen(other.screen)
{}

bool ScreenManager::nameExist(const std::string& name){
    auto& indexByString = screens.get<IndexByString>();
    auto found = indexByString.find(name);

    if(found != indexByString.end()) return true;
    return false;
}

bool ScreenManager::addScreen(const std::shared_ptr<ScreenInteface> screen, const std::string& name){
    if(nameExist(name)) return true;

    auto& indexByID = screens.get<IndexByID>();

    indexByID.insert(Pair(screen->getID(), name, screen)); // making copy

    return false;
}

ScreenID ScreenManager::getScreenID(const std::string& name){
    auto& indexByString = screens.get<IndexByString>();
    auto found = indexByString.find(name);
    
    if(found != indexByString.end()) return (*found).ID;
    return ScreenID();
}

std::string ScreenManager::getScreenName(const ScreenID& ID){
    auto& indexByID = screens.get<IndexByID>();
    auto found = indexByID.find(ID);

    if(found != indexByID.end()) return (*found).name;
    return std::string(); // empty string
}

void ScreenManager::mainLoop(sf::RenderWindow & window, const ScreenInteface& startID){
    ScreenID output = startID.getID();
    auto& indexByID = screens.get<IndexByID>();

    while(output.isValid()){
        auto tmp = indexByID.find(output);
        if(tmp == indexByID.end()) throw std::runtime_error("Cannot find screen.");

        output = (*tmp).screen->run(window);
    }
}


#endif