/*
 * Texture.h
 *
 *      Author: Kordowski Mateusz
 */


#ifndef TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_TEXTURE_H
#define TRAFFIC_SIM_MAIN_DRAWING_TEXTURE_TEXTURE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <vector>
#include <iostream>


namespace Drawing::Texture{

enum class TextureState{
    Removed,
    ExpectRemove,
    SetToRemove,
    Remain,
    Unknown
};


/**
 * @brief 
 * @details This class will be removed only when no one have it except for Texture::Manager.
 * 
 */
class Texture{
    friend class Manager;

    sf::Texture texture_;
    sf::IntRect portion_;
    bool request_for_deleting;

    Texture(const std::string& path, const sf::IntRect& area = sf::IntRect());
    Texture(const sf::Texture& texture, const sf::IntRect& area = sf::IntRect());

public:
    ~Texture();
    Texture(const Texture&) = delete;
    Texture(Texture&&) = delete;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&&) = delete;

    void requestRemove();
    bool shouldBeRemoved();
    void resetRemoveRequest();
    TextureState getState() const;

    sf::Texture& getTexture();
    sf::IntRect& getRect();

    const sf::Texture& getTexture_const() const;
    const sf::IntRect& getRect_const() const;
};

}

#endif
