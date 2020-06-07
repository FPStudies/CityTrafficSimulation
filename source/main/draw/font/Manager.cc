/*
 * Manager.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "font/Manager.h"

using namespace Draw::Font;

Manager::Manager() = default;

Manager::~Manager() = default;

bool Manager::load(const std::string& path, const std::string& alias){
    const std::lock_guard<std::mutex> lock(mutex_mod_map_);

    auto it = map_.find(alias);
    if(it != map_.end()) 
        return true;

    Font* raw_ptr = new Font(path);
    std::shared_ptr<Font> texture(raw_ptr);
    map_[alias] = texture;
    return false;
}

bool Manager::load(const std::string& path){
    return this->load(path, path);
}

bool Manager::save(const std::string& name, const sf::Font& object){
    const std::lock_guard<std::mutex> lock(mutex_mod_map_);
    
    auto it = map_.find(name);
    if(it != map_.end()) 
        return true;

    Font* raw_ptr = new Font(object);
    std::shared_ptr<Font> text(raw_ptr);
    map_[name] = text;
    return false;
}