/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */

#include "texture/Manager.h"

using namespace Drawing::Texture;

Manager::Manager() = default;

Manager::~Manager() = default;

Manager::Manager(Manager&& other)
: textures_(std::move(other.textures_))
{}

Manager& Manager::operator=(Manager&& other){
    textures_ = std::move(other.textures_);
    return *this;
}

bool Manager::loadTexture(const std::string& path, const std::string& alias, const sf::IntRect& area){
    auto it = textures_.find(alias);
    if(it != textures_.end()) 
        return true;

    Texture* raw_ptr = new Texture(path, area);
    std::shared_ptr<Texture> texture(raw_ptr);
    textures_[alias] = texture;
    return false;
}

bool Manager::loadTexture(const std::string& path){
    auto it = textures_.find(path);
    if(it != textures_.end()) 
        return true;

    Texture* raw_ptr = new Texture(path);
    std::shared_ptr<Texture> texture(raw_ptr);
    textures_[path] = texture;
    return true;
}

TextureState Manager::freeTexture(const std::string& name){
    auto it = textures_.find(name);
    if(it == textures_.end())
        return TextureState::Unknown;

    // TODO needs here synchronization
    if(it->second.use_count() <= 1){
        textures_.erase(it);
        return TextureState::Removed;
    }

    if(it->second->request_for_deleting){
        return TextureState::ExpectRemove;
    }
    else{
        it->second->request_for_deleting = true;
        return TextureState::SetToRemove;
    }
}

bool Manager::saveTexture(const std::string& name, const sf::Texture& texture, const sf::IntRect& rect){
    auto it = textures_.find(name);
    if(it != textures_.end()) 
        return true;

    Texture* raw_ptr = new Texture(texture, rect);
    std::shared_ptr<Texture> text(raw_ptr);
    textures_[name] = text;
    return false;
}

std::shared_ptr<Texture> Manager::getTexture(const std::string& name) const{
    auto it = textures_.find(name);
    if(it == textures_.end())
        return std::shared_ptr<Texture>();

    return it->second;
}
