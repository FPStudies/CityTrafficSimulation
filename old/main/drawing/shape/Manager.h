/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_SHAPE_MANAGER_DEF_H
#define TRAFFIC_SIM_MAIN_DRAWING_SHAPE_MANAGER_DEF_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>

#include "../texture/Manager.h"

namespace Draw::Shape{

using TextManager = ::Draw::Texture::Manager;

class Manager{
    typedef std::map<std::string, std::shared_ptr<sf::Shape>> MyMap; // used for storing shapes

    MyMap shapes_;
    TextManager& texture_manager_;

public:
    Manager(TextManager& manager);
    ~Manager();
    Manager(const Manager&) = delete;
    Manager(Manager&& other);
    Manager& operator=(Manager&& other);

    bool createRectangle(const std::string& path, const std::string& alias, const sf::IntRect& area);
    bool loadTexture(const std::string& path, const std::string& alias);
    bool loadTexture(const std::string& path);

    bool freeTexture(const std::string& name);

    /**
     * @brief Save the texture that was created outside this object.
     * 
     * @param texture 
     * @return true - if saving did not succeeded
     * @return false - if saving did succeeded
     */
    bool saveShape(const std::shared_ptr<sf::Shape>& texture);

    sf::Texture& getTexture(const std::string& name) const;
    sf::IntRect getIntRect(const std::string& name) const;

};
}

#endif
