/*
 * ScreenManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_SCREEN_MANAGER_CC
#define TRAFFIC_SIM_SCREEN_MANAGER_CC

#include "ScreenManager.h"

ScreenManager::ScreenManager() {}

ScreenManager::~ScreenManager() {}

ScreenManager::Pair::Pair(const ScreenID& ID, const std::string& name, const std::shared_ptr<ScreenInteface>& screen)
: ID_(ID), name_(name), screen_(screen)
{}

ScreenManager::Pair::Pair(const Pair& other)
: ID_(other.ID_), name_(other.name_), screen_(other.screen_)
{}

bool ScreenManager::nameExist(const std::string& name){
    auto& index_by_string = screens_.get<IndexByString>();
    auto found = index_by_string.find(name);

    if(found != index_by_string.end())
        return true;
    return false;
}

bool ScreenManager::addScreen(const std::shared_ptr<ScreenInteface> screen, const std::string& name){
    if(nameExist(name))
        return true;

    auto& index_by_ID = screens_.get<IndexByString>();

    index_by_ID.insert(Pair(screen->getID(), name, screen)); // making copy

    return false;
}

ScreenID ScreenManager::getScreenID(const std::string& name){
    auto& index_by_string = screens_.get<IndexByString>();
    auto found = index_by_string.find(name);
    
    if(found != index_by_string.end())
        return (*found).ID_;
    return ScreenID();
}

std::string ScreenManager::getScreenName(const ScreenID& ID){
    auto& index_by_ID = screens_.get<IndexByID>();
    auto found = index_by_ID.find(ID);

    if(found != index_by_ID.end())
        return (*found).name_;
    return std::string(); // empty string
}

void ScreenManager::mainLoop(std::shared_ptr<sf::RenderWindow>& window, const ScreenInteface& start_ID){
    ScreenID output = start_ID.getID();
    auto& index_by_ID = screens_.get<IndexByID>();

    while(output.isValid()){
        auto tmp = index_by_ID.find(output);
        if(tmp == index_by_ID.end())
            throw std::runtime_error("Cannot find screen.");

        output = (*tmp).screen_->run(window);
    }
}

void ScreenManager::mainLoop(std::shared_ptr<sf::RenderWindow>& window, const std::string& name){
    auto& index_by_string = screens_.get<IndexByString>();
    auto& index_by_ID = screens_.get<IndexByID>();
    auto test = index_by_string.find(name);
    if (test == index_by_string.end())
        return;

    ScreenID output = test->ID_;

    while(output.isValid()){
        auto tmp = index_by_ID.find(output);
        if(tmp == index_by_ID.end())
            throw std::runtime_error("Cannot find screen.");

        output = (*tmp).screen_->run(window);
    }
}

#endif