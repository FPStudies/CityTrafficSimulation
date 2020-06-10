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
#include "../../utility/Singleton.hpp"


namespace Draw::Texture{

/**
 * @brief Singleton used to store the textures. It ensure that a texture was loaded once and will not be deleted if other objects still retains ownership.
 * 
 */
class Manager final: public ::SharedResource::Manager<Texture, sf::Texture>, public ::Utils::Singleton<Manager>{
    friend class ::Utils::Singleton<Manager>;
    friend class ::Utils::SingletonDestroyer<Manager>;

    virtual bool save(const std::string& name, const sf::Texture& object) override;
    Manager();
    virtual ~Manager();

public:
    Manager(const Manager&) = delete;
    Manager& operator=(Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(Manager&& other) = delete;

    /**
     * @brief Load a texture from the file.
     * 
     * @param path 
     * @param alias 
     * @param area 
     * @return true - if texture was not loaded successfully and the alias was not occupied.
     * @return false - if texture was loaded successfully.
     */
    bool load(const std::string& path, const std::string& alias, const sf::IntRect& area);
    
    /**
     * @brief Load a texture from the file.
     * 
     * @param path 
     * @param alias 
     * @return true - if texture was not loaded successfully and the alias was not occupied.
     * @return false - if texture was loaded successfully.
     */
    virtual bool load(const std::string& path, const std::string& alias) override;

    /**
     * @brief Load a texture from the file.
     * 
     * @param path 
     * @return true - if texture was not loaded successfully and the alias was not occupied.
     * @return false - if texture was loaded successfully.
     */
    virtual bool load(const std::string& path) override;

    /**
     * @brief Save the texture that was created outside this object.
     * It copy the texture object.
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
