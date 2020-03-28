#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <memory>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "drawable.h"
#include "drawingID.h"

class DrawManagerBridgeToSets;

/**
 * @brief Class used to draw stored objects.
 * In the assumption, only factories will be able to add or remove certain objects.
 */
class DrawManager{
    friend class DrawManagerBridgeToSets;

    // for now list but it will be better with R* algorithm.
    using Container = std::map<DrawingID, std::shared_ptr<Drawable>>;
    using WindowCont = std::vector<std::weak_ptr<sf::RenderWindow>>;

    Container toDraw;

    std::shared_ptr<sf::RenderWindow> objectWindow;

    static WindowCont windowsStatic;



    void add(std::shared_ptr<Drawable> entity);

    void remove(std::shared_ptr<Drawable> entity);

    DrawManager(std::shared_ptr<sf::RenderWindow>& window);
    
    DrawManager(const DrawManager& other) = delete;

public:
    DrawManager(const DrawManager&& other);
    ~DrawManager();
    
    static DrawManager create(std::shared_ptr<sf::RenderWindow>& window);

    void drawAll();

};


#endif
