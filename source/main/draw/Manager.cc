/*
 * Manager.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Manager.h"

using namespace Draw;

const unsigned int Manager::DrawLayer::DEFAULT_LIST_SIZE = 50;

const unsigned int Manager::max_instances_ = 1;

std::mutex Manager::mutex_change_state_static_;

unsigned int Manager::ref_count_;

std::list<std::pair<Manager*, int>> Manager::instances_;



Manager::DrawLayer::DrawLayer(const std::string& name, const std::shared_ptr<Screen::View>& view) 
: name_(name), container_(), render_(DEFAULT_LIST_SIZE), view_(view), mutex_modify_()
{}

Manager::DrawLayer::~DrawLayer() = default;

bool Manager::DrawLayer::remove(std::shared_ptr<Drawable>& entity){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    ObjectPair::iterator it = container_.find(entity->getID());

    if(it != container_.end()){
        it->second = nullptr;
        container_.erase(it);
        return false;
    }
    return true;
}

void Manager::DrawLayer::clearNulls(){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    for(auto it = render_.begin(); it != render_.end();){
        if(it->get() == nullptr){
            it = render_.erase(it);
        }
        else{
            ++it;
        }
    }
}

void Manager::DrawLayer::add(std::shared_ptr<Drawable>& entity){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    container_[entity->getID()] = entity;
    render_.push_back(entity);
}

const std::string& Manager::DrawLayer::getName() const{
    std::lock_guard<std::mutex> guard(mutex_modify_);
    return name_;
}

void Manager::DrawLayer::setName(const std::string& name){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    this->name_ = name;
}

void Manager::DrawLayer::draw(sf::RenderWindow& window){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    window.setActive();
    window.setView(view_->getView());
    for(auto it = render_.begin(); it != render_.end(); ++it){
        auto& sec = *it;
        if(sec && sec->canBeDrawn())
            sec->draw(window);
    }
}

std::shared_ptr<Screen::View> Manager::DrawLayer::getView() const{
    return view_;
}









bool Manager::addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity){ //check if reference or copy
    std::lock_guard<std::mutex> guard(mutex_modify_);
    for(auto it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == layer_name){
            (*it)->add(entity);
            return false;
        }
    }
    return true;
}

bool Manager::addFirstLayer(const std::string& layer_name, const std::shared_ptr<Screen::View>& view){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    if(to_draw_.size() != 0)
        return true;
    to_draw_.push_back(std::make_unique<DrawLayer>(layer_name, view));
    return false;
}

bool Manager::addLayerBefore(const std::string& previous_layer_name, const std::string& layer_name, const std::shared_ptr<Screen::View>& view){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    for(auto it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == previous_layer_name){
            to_draw_.insert(it, std::make_unique<DrawLayer>(layer_name, view));
            return false;
        }
    }
    return true;
}

bool Manager::addLayerAfter(const std::string& next_layer_name, const std::string& layer_name, const std::shared_ptr<Screen::View>& view){
    std::lock_guard<std::mutex> guard(mutex_modify_);
    for(auto it = to_draw_.begin(); it != to_draw_.end(); ++it){
        if((*it)->getName() == next_layer_name){
            ++it;
            to_draw_.insert(it, std::make_unique<DrawLayer>(layer_name, view));
            return false;
        }
    }
    return true;
}

bool Manager::remove(const std::string& layer_name, std::shared_ptr<Drawable> entity){ //check if reference or copy
    std::lock_guard<std::mutex> guard(mutex_modify_);
    auto it = to_draw_.begin();
    while(it != to_draw_.end()){
        if((*it)->getName() == layer_name){
            return (*it)->remove(entity);
        }
    }
    return true;
}

Manager::Manager(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<Screen::View>& view)
: to_draw_(), object_window_(window), mutex_modify_()
{
    addFirstLayer(layer_name, view);
}


Manager::~Manager(){
    std::lock_guard<std::mutex> guard(mutex_change_state_static_);
    auto itEnd = instances_.end();
    for(auto it = instances_.begin(); it != itEnd; ++it){
        if(this == it->first){
            instances_.erase(it);
            break;
        }
            
    }
    --ref_count_;
}

Manager::Manager(Manager&& other) noexcept
: to_draw_(std::move(other.to_draw_)), object_window_(std::move(other.object_window_))
{}

std::unique_ptr<Manager> Manager::create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<Screen::View>& view){
    std::lock_guard<std::mutex> guard(mutex_change_state_static_);
    if(ref_count_ >= max_instances_){
        throw std::invalid_argument("The limit of Draw::Manager instances have been reached.");
    }
    ++ref_count_;

    Manager* draw_ptr = new Manager(layer_name, window, view);
    instances_.push_back(std::make_pair(draw_ptr, 1));
    return std::move(std::unique_ptr<Manager>(draw_ptr));
}

bool Manager::draw(const std::string& layer_name_first, const std::string& layer_name_last){
    auto it = to_draw_.begin();
    bool start = false;
    
    if(layer_name_first == layer_name_last){
        while(it != to_draw_.end()){
            if((*it)->getName() == layer_name_first){
                (*it)->draw(*object_window_);
                return false;
            }
            ++it;
        }
    }
    else{
        while(it != to_draw_.end()){
            if((*it)->getName() == layer_name_first){
                start = true;
                (*it)->draw(*object_window_);
            }
            else if((*it)->getName() == layer_name_last){
                if(start){
                    (*it)->draw(*object_window_);
                    return false;
                }
                return true;
            }
            else if(start){
                (*it)->draw(*object_window_);
            }
            ++it;
        }
    }

    return true;
}

void Manager::drawAll(){
    for(auto& it : to_draw_){
        it->draw(*object_window_);
    }
}

bool Manager::drawLayer(const std::string& layer_name){
    auto it = to_draw_.begin();
    while(it != to_draw_.end()){
        if((*it)->getName() == layer_name){
            (*it)->draw(*object_window_);
            return false;
        }
        ++it;
    }
    return true;
}

void Manager::clearNulls(){
    for(auto& it : to_draw_){
        it->clearNulls();
    }
}

void Manager::clearNulls(const std::string& layer_name){
    for(auto& it : to_draw_){
        if(it->getName() == layer_name){
            it->clearNulls();
            break;
        }
    }
}
