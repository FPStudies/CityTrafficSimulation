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
#include "../../utility/Singleton.hpp"


namespace Draw::Font{

class Manager final: public ::SharedResource::Manager<Font, sf::Font>, public ::Utils::Singleton<Manager>{
    friend class ::Utils::Singleton<Manager>;
    friend class ::Utils::SingletonDestroyer<Manager>;
    
    Manager();
    virtual ~Manager();
public:
    
    Manager(const Manager&) = delete;
    Manager& operator=(Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(Manager&&) = delete;

    virtual bool load(const std::string& path, const std::string& alias) override;
    virtual bool load(const std::string& path) override;

    virtual bool save(const std::string& name, const sf::Font& object) override;

};
}

#endif
