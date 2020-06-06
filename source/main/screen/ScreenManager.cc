/*
 * ScreenManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_SCREEN_MANAGER_CC
#define TRAFFIC_SIM_SCREEN_MANAGER_CC

#include "ScreenManager.h"

ScreenManager::ScreenManager() = default;

ScreenManager::~ScreenManager() = default;

bool ScreenManager::addScreen(const std::shared_ptr<ScreenInteface> screen, const std::string& name){
    return Inher::add(screen, screen->getID(), name);
}

ScreenID ScreenManager::getScreenID(const std::string& name) const{
    return Inher::getKeyOne(name);
}

std::string ScreenManager::getScreenName(const ScreenID& ID) const{
    return Inher::getKeyTwo(ID);
}

bool ScreenManager::remove(const ScreenID& ID){
    return Inher::remove(ID);
}

bool ScreenManager::remove(const std::string& name){
    return Inher::remove(name);
}

void ScreenManager::mainLoop(std::shared_ptr<sf::RenderWindow>& window, const ScreenInteface& start_ID){
    ScreenID output = start_ID.getID();
    auto& index_by_ID = map_.get<IndexByKeyOne>();

    while(output.isValid()){
        auto tmp = index_by_ID.find(output);
        if(tmp == index_by_ID.end())
            throw std::runtime_error("Cannot find screen.");

        output = (*tmp).shared_variable_->run(window);
    }
}

void ScreenManager::mainLoop(std::shared_ptr<sf::RenderWindow>& window, const std::string& name){
    auto& index_by_string = map_.get<IndexByKeyTwo>();
    auto& index_by_ID = map_.get<IndexByKeyOne>();
    auto test = index_by_string.find(name);
    if (test == index_by_string.end())
        return;

    ScreenID output = test->key_one_;

    while(output.isValid()){
        auto tmp = index_by_ID.find(output);
        if(tmp == index_by_ID.end())
            throw std::runtime_error("Cannot find screen.");

        output = (*tmp).shared_variable_->run(window);
    }
}

#endif
