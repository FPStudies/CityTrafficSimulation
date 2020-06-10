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
 * @details The object to draw are divided by layers. 
 * Each layer have specific position based on previous and next layers. It can be presented as a list.
 * Each layer can be drawn independently, from a range of layers or all layers can be drawn.
 * 
 * A manager can only have a predetermined number of instances (default is 1, cannot be changed).
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
        std::shared_ptr<::ScreenMaster::View> view_;
        

    public:
        DrawLayer(const std::string& name, const std::shared_ptr<::ScreenMaster::View>& view);
        virtual ~DrawLayer();
        DrawLayer(const DrawLayer&) = delete;

        bool remove(std::shared_ptr<Drawable>& entity);
        void add(std::shared_ptr<Drawable>& entity);

        const std::string& getName() const;
        void setName(const std::string& name);
        void draw(sf::RenderWindow& window);

        void clearNulls();

        std::shared_ptr<::ScreenMaster::View> getView() const;
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
    

    Manager(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<::ScreenMaster::View>& view);
    
    Manager(const Manager& other) = delete;

    bool addFirstLayer(const std::string& layer_name, const std::shared_ptr<::ScreenMaster::View>& view);

public:
    Manager(Manager&& other) noexcept;
    ~Manager();
    
    
    /**
     * @brief Create an instance of The Draw::Manager or throw an runtime_error if the limit of instances has been reached.
     * It also remembers the created instance.
     * 
     * @param layer_name - name of the first layer.
     * @param window - a window that will be associated with newly created instance. It will be used to draw objects.
     * @param view - view that will be used while drawing objects.
     * @return std::unique_ptr<Manager> - returned pointer to the Manager.
     */
    static std::unique_ptr<Manager> create(const std::string& layer_name, std::shared_ptr<sf::RenderWindow>& window, const std::shared_ptr<::ScreenMaster::View>& view);

    /**
     * @brief Draw from a range of layers
     * 
     * @param layer_name_first - the first layer to draw
     * @param layer_name_last - the last layer that will be drawn
     * @return true - if the range was not correctly specified. It can draw a part of the specified range that begins with layer_name_first.
     * @return false - if the range was correctly specified and drawn.
     */
    bool draw(const std::string& layer_name_first, const std::string& layer_name_last);

    /**
     * @brief Draw all layers.
     * 
     */
    void drawAll();

    /**
     * @brief Draw specified layer.
     * 
     * @param layer_name - name of the layer
     * @return true - if the layer was not found and nothing was drawn.
     * @return false - if layer was found and drawn.
     */
    bool drawLayer(const std::string& layer_name);

    /**
     * @brief Draw an entity which is in the given layer.
     * 
     * @param layer_name - name of the layer.
     * @param entity - shared ponter to the entity.
     * @return true - if the entity was not found in specified layer.
     * @return false - if entity was found in specified layer and drawn.
     */
    bool addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity);

    /**
     * @brief Adds layer before specified layer.
     * 
     * @param previous_layer_name
     * @param layer_name 
     * @param view - a view used by this layer.
     * @return true - if the previous_layer_name cannot be found.
     * @return false - if the layer was added.
     */
    bool addLayerBefore(const std::string& previous_layer_name, const std::string& layer_name, const std::shared_ptr<::ScreenMaster::View>& view);

    /**
     * @brief Adds layer after specified layer.
     * 
     * @param next_layer_name 
     * @param layer_name 
     * @param view - a view used by this layer.
     * @return true - if the previous_layer_name cannot be found.
     * @return false - if the layer was added.
     */
    bool addLayerAfter(const std::string& next_layer_name, const std::string& layer_name, const std::shared_ptr<::ScreenMaster::View>& view);

    /**
     * @brief Remove an entity from specified layer.
     * @details It does not modify any of the structures. It only sets a corresponding pointer to nullptr to not have an impact on performance.
     * That kind of object can be referen as Zombie.
     * 
     * @param layer_name 
     * @param entity - shared pointer of the entity that should be removed.
     * @return true - if an layer or entity within layer cannot be found.
     * @return false - if the entity was removved successfully.
     */
    bool remove(const std::string& layer_name, std::shared_ptr<Drawable> entity);

    /**
     * @brief Clears all of the Zombie objects in all layers. This operation can be impactful to the performance.
     * 
     */
    void clearNulls();

    /**
     * @brief Clear all of the Zombie objects in specified layer. This operation can be impactful to the performance.
     * 
     * @param layer_name 
     */
    void clearNulls(const std::string& layer_name);

};

}

#endif
