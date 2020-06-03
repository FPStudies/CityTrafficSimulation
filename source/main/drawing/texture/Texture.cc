/*
 * Texture.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "texture/Texture.h"


using namespace Drawing::Texture;

Texture::Texture(const std::string& path, const sf::IntRect& area)
: texture_(), portion_(area), request_for_deleting(false)
{
    sf::Texture text;
    if(!text.loadFromFile(path)){
        std::cerr << "Could not load texture file: " << path << "\n";
    }

    texture_ = std::move(text);
}

Texture::Texture(const sf::Texture& texture, const sf::IntRect& area)
: texture_(texture), portion_(area), request_for_deleting(false)
{}

Texture::~Texture() = default;


void Texture::requestRemove(){
    request_for_deleting = true;
}

bool Texture::shouldBeRemoved(){
    return request_for_deleting;
}

void Texture::resetRemoveRequest(){
    request_for_deleting = false;
}

TextureState Texture::getState() const{
    if(request_for_deleting)
        return TextureState::ExpectRemove;
    return TextureState::Remain;
}

sf::Texture& Texture::getTexture() {
    return texture_;
}

sf::IntRect& Texture::getRect(){ 
    return portion_;
}

const sf::Texture& Texture::getTexture_const() const{
    return texture_;
}
const sf::IntRect& Texture::getRect_const() const{
    return portion_;
}
