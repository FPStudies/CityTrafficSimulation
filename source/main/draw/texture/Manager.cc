/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */

#include "texture/Manager.h"

using namespace Draw::Texture;

Manager::Manager() = default;

Manager::~Manager() = default;

bool Manager::load(const std::string& path, const std::string& alias, const sf::IntRect& area){
    const std::lock_guard<std::mutex> lock(mutex_mod_map_);

    auto it = map_.find(alias);
    if(it != map_.end()) 
        return true;

    Texture* raw_ptr = new Texture(path, area);
    std::shared_ptr<Texture> texture(raw_ptr);
    map_[alias] = texture;
    return false;
}

bool Manager::load(const std::string& path, const std::string& alias){
    return this->load(path, alias, sf::IntRect());
}

bool Manager::load(const std::string& path){
    return this->load(path, path, sf::IntRect());
}

bool Manager::save(const std::string& name, const sf::Texture& object){
    const std::lock_guard<std::mutex> lock(mutex_mod_map_);

    auto it = map_.find(name);
    if(it != map_.end()) 
        return true;

    Texture* raw_ptr = new Texture(object);
    std::shared_ptr<Texture> text(raw_ptr);
    map_[name] = text;
    return false;
}

bool Manager::save(const std::string& name, const sf::Texture& texture, const sf::IntRect& rect){
    const std::lock_guard<std::mutex> lock(mutex_mod_map_);
    
    auto it = map_.find(name);
    if(it != map_.end()) 
        return true;

    Texture* raw_ptr = new Texture(texture, rect);
    std::shared_ptr<Texture> text(raw_ptr);
    map_[name] = text;
    return false;
}
