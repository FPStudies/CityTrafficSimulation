/*
 * Manager.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "font/Manager.h"

using namespace Draw::Font;

Manager* Manager::instance_ = nullptr;

Manager::Manager() = default;

Manager::~Manager() = default;

Manager& Manager::getInstance(){
    if(!instance_){
        const std::lock_guard<std::mutex> lock(Manager::mutex_);
        if(!instance_)
            instance_ = new Manager;
    }
    return *instance_;
}

bool Manager::load(const std::string& path, const std::string& alias){
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
    auto it = map_.find(name);
    if(it != map_.end()) 
        return true;

    Font* raw_ptr = new Font(object);
    std::shared_ptr<Font> text(raw_ptr);
    map_[name] = text;
    return false;
}