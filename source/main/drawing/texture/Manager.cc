/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */

#include "texture/Manager.h"

using namespace Drawing::Texture;

Manager::Texture::Texture(const std::string& path, const sf::IntRect& area)
: texture_(), portion_(area), request_for_deleting(false)
{
    sf::Texture text;
    if(!text.loadFromFile(path)){
        std::cerr << "Could not load texture file: " << path << "\n";
    }

    texture_ = std::move(text);
}

Manager::Texture::Texture(const sf::Texture& texture, const sf::IntRect& area)
: texture_(texture), portion_(area), request_for_deleting(false)
{}

Manager::Texture::~Texture() = default;


void Manager::Texture::requestRemove(){
    request_for_deleting = true;
}

bool Manager::Texture::shouldBeRemoved(){
    return request_for_deleting;
}

void Manager::Texture::resetRemoveRequest(){
    request_for_deleting = false;
}

Manager::TextureState Manager::Texture::getState(){
    if(request_for_deleting)
        return TextureState::ExpectRemove;
    return TextureState::Remain;
}

sf::Texture& Manager::Texture::getTexture(){
    return texture_;
}

sf::IntRect& Manager::Texture::getRect(){
    return portion_;
}

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

Manager::TextureState Manager::freeTexture(const std::string& name){
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

std::shared_ptr<Manager::Texture> Manager::getTexture(const std::string& name) const{
    auto it = textures_.find(name);
    if(it == textures_.end())
        return std::shared_ptr<Manager::Texture>();

    return it->second;
}
