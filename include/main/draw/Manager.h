/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_DRAW_MANAGER_H
#define TRAFFIC_SIM_MAIN_DRAW_MANAGER_H

#include <memory>
#include <map>
#include <vector>
#include <deque>
#include <list>
#include <memory>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "DrawID.h"
#include "../screen/View.h"

namespace Draw{

/**
 * @brief Class used to draw stored objects.
 * In the assumption, only factories will be able to add or remove certain objects.
 */
class Manager{

    // for now list but it will be better with R* algorithm.
    using WindowCont = std::list<std::weak_ptr<sf::RenderWindow>>;
    
    class DrawLayer{
        using ObjectPair = std::map<DrawID, std::shared_ptr<Drawable>>;
        using ToRender = std::list<std::shared_ptr<Drawable>>;
        static const unsigned int DEFAULT_LIST_SIZE;

        std::string name_;
        ObjectPair container_;
        ToRender render_;
        std::shared_ptr<::Screen::View> view_;
        mutable std::mutex mutex_modify_;
        

    public:
        DrawLayer(const std::string& name, const std::shared_ptr<::Screen::View>& view);
        virtual ~DrawLayer();
        DrawLayer(const DrawLayer&) = delete;

        bool remove(std::shared_ptr<Drawable>& entity);
        void add(std::shared_ptr<Drawable>& entity);

        const std::string& getName() const;
        void setName(const std::string& name);
        void draw(sf::RenderWindow& window);

        void clearNulls();

        std::shared_ptr<::Screen::View> getView() const;
    };

    using Layers = std::deque<std::unique_ptr<DrawLayer>>;


    Layers to_draw_;
    std::shared_ptr<sf::RenderWindow> object_window_;
    std::mutex mutex_modify_;
    static std::mutex mutex_change_state_static_;
    

    static unsigned int ref_count_;
    const static unsigned int max_instances_;

    /**
     * @brief It stores only a place in memory and will never be dereferenced,
     * so it doesn't bother that unique_ptr will delete it.
     * Moreover it will be deleted while invoking destructor. 
     * 
     */
    static std::list<std::pair<Manager*, int>> instances_;
    

    Manager(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<::Screen::View>& view);
    
    Manager(const Manager& other) = delete;

public:
    Manager(Manager&& other) noexcept;
    ~Manager();
    
    // use std::move
    
    static std::unique_ptr<Manager> create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<::Screen::View>& view);

    bool draw(const std::string& layer_name_first, const std::string& layer_name_last);

    void drawAll();

    bool drawLayer(const std::string& layer_name);

    bool addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity);

    bool addFirstLayer(const std::string& layer_name, const std::shared_ptr<::Screen::View>& view);

    bool addLayerBefore(const std::string& previous_layer_name, const std::string& layer_name, const std::shared_ptr<::Screen::View>& view);
    bool addLayerAfter(const std::string& next_layer_name, const std::string& layer_name, const std::shared_ptr<::Screen::View>& view);

    bool remove(const std::string& layer_name, std::shared_ptr<Drawable> entity);

    void clearNulls();

    void clearNulls(const std::string& layer_name);

};

}

#endif
