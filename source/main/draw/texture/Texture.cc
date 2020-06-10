/*
 * Texture.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "texture/Texture.h"


using namespace Draw::Texture;

Texture::Texture(const std::string& path, const sf::IntRect& area)
: ::SharedResource::Resource<sf::Texture>(), portion_(area)
{
    sf::Texture text;
    if(!text.loadFromFile(path)){
        std::cerr << "Could not load texture file: " << path << "\n";
    }

    object_ = std::move(text);
}

Texture::Texture(const sf::Texture& texture, const sf::IntRect& area)
: ::SharedResource::Resource<sf::Texture>(texture), portion_(area)
{}



sf::IntRect& Texture::getRect(){ 
    return portion_;
}

const sf::IntRect& Texture::getRect_const() const{
    return portion_;
}
