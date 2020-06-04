/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_FONT_MANAGER_H
#define TRAFFIC_SIM_MAIN_DRAWING_FONT_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <iostream>

#include "Font.h"
#include "../../utility/SharedResourceManager.hpp"


namespace Drawing::Font{

class Manager: public ::SharedResource::Manager<Font, sf::Font>{
    static Manager* instance_;

    Manager();
    
public:
    virtual ~Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(Manager&&) = delete;

    static Manager& getInstance();

    virtual bool load(const std::string& path, const std::string& alias) override;
    virtual bool load(const std::string& path) override;

    virtual bool save(const std::string& name, const sf::Font& object) override;

};
}

#endif
