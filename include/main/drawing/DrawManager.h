/*
 * DrawManager.h
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
#include "DrawingID.h"

class DrawManagerBridgeToSets;

/**
 * @brief Class used to draw stored objects.
 * In the assumption, only factories will be able to add or remove certain objects.
 */
class DrawManager{
    friend class DrawManagerBridgeToSets;

    // for now list but it will be better with R* algorithm.
    using ObjectPair = std::map<DrawingID, std::shared_ptr<Drawable>>;
    using WindowCont = std::vector<std::weak_ptr<sf::RenderWindow>>;
    
    class DrawLayer{
        using ObjectPair = std::map<DrawingID, std::shared_ptr<Drawable>>;

        std::string name_;
        ObjectPair container_;

    public:
        DrawLayer(const std::string& name);
        virtual ~DrawLayer();
        DrawLayer(const DrawLayer&) = delete;

        ObjectPair& getContainer();
        bool remove(std::shared_ptr<Drawable>& entity);
        void add(std::shared_ptr<Drawable>& entity);

        const std::string& getName();
        void setName(const std::string& name);
        void draw();

    };

    using List = std::list<std::unique_ptr<DrawLayer>>;


    List to_draw_;
    std::shared_ptr<sf::RenderWindow> object_window_;

    static WindowCont windows_static_;
    

    DrawManager(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window);
    
    DrawManager(const DrawManager& other) = delete;

public:
    DrawManager(DrawManager&& other) noexcept;
    ~DrawManager();
    
    // use std::move
    static DrawManager create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window);

    void drawAll();

    bool drawLayer(const std::string& layer_name);

    bool addEntity(const std::string& layer_name, std::shared_ptr<Drawable>& entity);

    void addFirstLayer(const std::string& layer_name);

    bool addLayer(const std::string& previous_layer_name, const std::string& layer_name);

    bool remove(const std::string& layer_name, std::shared_ptr<Drawable>& entity);

};


#endif
