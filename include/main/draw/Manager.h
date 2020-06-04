/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAW_MANAGER_H
#define TRAFFIC_SIM_DRAW_MANAGER_H

#include <memory>
#include <map>
#include <vector>
#include <list>

#include <SFML/Graphics.hpp>

#include "Drawable.h"
#include "DrawID.h"

namespace Draw{

/**
 * @brief Class used to draw stored objects.
 * In the assumption, only factories will be able to add or remove certain objects.
 */
class Manager{

    // for now list but it will be better with R* algorithm.
    using WindowCont = std::vector<std::weak_ptr<sf::RenderWindow>>;
    
    class DrawLayer{
        using ObjectPair = std::map<DrawID, std::shared_ptr<Drawable>>;
        using ToRender = std::list<std::shared_ptr<Drawable>>;
        static const unsigned int DEFAULT_LIST_SIZE;

        std::string name_;
        ObjectPair container_;
        ToRender render_;

    public:
        DrawLayer(const std::string& name);
        virtual ~DrawLayer();
        DrawLayer(const DrawLayer&) = delete;

        bool remove(std::shared_ptr<Drawable>& entity);
        void add(std::shared_ptr<Drawable>& entity);

        const std::string& getName();
        void setName(const std::string& name);
        void draw(sf::RenderTarget& target);

        void clearNulls();

    };

    using Layers = std::vector<std::unique_ptr<DrawLayer>>;


    Layers to_draw_;
    std::shared_ptr<sf::RenderWindow> object_window_;

    static WindowCont windows_static_;
    

    Manager(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window);
    
    Manager(const Manager& other) = delete;

public:
    Manager(Manager&& other) noexcept;
    ~Manager();
    
    // use std::move
    static std::unique_ptr<Manager> create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window);

    void drawAll();

    bool drawLayer(const std::string& layer_name);

    bool addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity);

    void addFirstLayer(const std::string& layer_name);

    bool addLayer(const std::string& previous_layer_name, const std::string& layer_name);

    bool remove(const std::string& layer_name, std::shared_ptr<Drawable> entity);

    void clearNulls();

    void clearNulls(const std::string& layer_name);

};

}

#endif
