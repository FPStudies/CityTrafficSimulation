/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_MANAGER_H
#define TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <iostream>

#include "Texture.h"
#include "../../utility/SharedResourceManager.hpp"


namespace Draw::Texture{

class Manager: public ::SharedResource::Manager<Texture, sf::Texture>{
    static Manager* instance_;

    virtual bool save(const std::string& name, const sf::Texture& object) override;
    Manager();

public:
    virtual ~Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(Manager&& other) = delete;

    static Manager& getInstance();

    bool load(const std::string& path, const std::string& alias, const sf::IntRect& area);
    virtual bool load(const std::string& path, const std::string& alias) override;
    virtual bool load(const std::string& path) override;

    /**
     * @brief Save the texture that was created outside this object.
     * It copy the texture.
     * 
     * @param name - what name should be given to this texture
     * @param texture
     * @param rect
     * @return true - if saving did not succeeded
     * @return false - if saving did succeeded
     */
    bool save(const std::string& name, const sf::Texture& texture, const sf::IntRect& rect = sf::IntRect());

};
}

#endif
