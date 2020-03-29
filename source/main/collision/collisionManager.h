#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <memory>
#include <vector>

#include "collisionInterface.h"

class CollisionManager{
    friend class CollisionManagerBridgeToSets;

    // or use spatial partitioning algorithm like R*
    using Container = std::vector<CollisionInterface>;

    Container toCollisionCheck;

    void addEntity(std::shared_ptr<CollisionInterface>& entity);

    bool remove(std::shared_ptr<CollisionInterface>& entity);

    CollisionManager();
    CollisionManager(const CollisionManager&) = delete;

public:
    CollisionManager(const CollisionManager&& other);
    ~CollisionManager();

    void checkCollisions();

    // use std::move
    static CollisionManager create(std::shared_ptr<sf::RenderWindow>& window);

};

#endif