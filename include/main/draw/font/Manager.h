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

/**
 * @brief Singleton used to store the fonts. It ensure that a font was loaded once and will not be deleted if other objects still retains ownership.
 * 
 */
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

    /**
     * @brief Load a font from the file.
     * 
     * @param path 
     * @param alias 
     * @return true - if font was not loaded successfully and the alias was not occupied.
     * @return false - if font was loaded successfully.
     */
    virtual bool load(const std::string& path, const std::string& alias) override;

    /**
     * @brief Load a font from the file.
     * 
     * @param path 
     * @return true - if font was not loaded successfully and the alias was not occupied.
     * @return false - if font was loaded successfully.
     */
    virtual bool load(const std::string& path) override;

    /**
     * @brief Save the font that was created outside this object.
     * It copy the font object.
     * 
     * @param name 
     * @param object 
     * @return true - if saving did not succeeded
     * @return false - if saving did succeeded
     */
    virtual bool save(const std::string& name, const sf::Font& object) override;

};
}

#endif
