/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_SPRITE_MANAGER_DEF_H
#define TRAFFIC_SIM_MAIN_DRAWING_SPRITE_MANAGER_DEF_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <functional>

#include "../texture/Manager.h"

namespace Draw::Sprite{

using TextManager = ::Draw::Texture::Manager;

class Manager{
    struct Portion{
        // shared to keep the texture until deleting sprite. This prevens using sprite on deleted texture.
        std::shared_ptr<sf::Texture> texture_;
        std::shared_ptr<sf::Sprite> sprite_;
    };

    typedef std::map<std::string, std::reference_wrapper<Portion>> MyMap;

    MyMap sprites_;
    TextManager& texture_manager_;

public:
    Manager(TextManager& manager);
    ~Manager();
    Manager(const Manager&) = delete;
    Manager(Manager&& other);
    Manager& operator=(Manager&& other);

    bool loadSprite(const std::string& textureName, const std::string& alias, const sf::IntRect& area);
    bool loadSprite(const std::string& textureName, const std::string& alias);
    bool loadSprite(const std::string& textureName);

    bool freeSprite(const std::string& name);

    /**
     * @brief Save the sprite that was created outside this object.
     * 
     * @param texture 
     * @return true 
     * @return false 
     */
    bool saveSprite(const sf::Sprite& sprite);

    sf::Sprite& getSpriteReferencr(const std::string& name) const;
    std::shared_ptr<sf::Sprite> getSpritePointer(const std::string& name) const;

};
}

#endif
