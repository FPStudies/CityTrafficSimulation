#ifndef ZPR_TRAFFIC_SIM_DRAWABLE_H
#define ZPR_TRAFFIC_SIM_DRAWABLE_H

#include <memory>
#include <vector>
#include <box2d/box2d.h>

#include "collisionInterface.h"

/**
 * @brief Class that manages all of the objects, that can sense other objects.
 * CollisionManager should be put into world contact listener to manage all of the objets in it.
 * It is used in combination with other Sets that work as factory to ensure that the newly created object is in the object warehouse.
 * 
 */

class CollisionManager: public b2ContactListener{
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

    // I think this is not needed anymore
    //void checkCollisions();

    // use std::move after creation
    static CollisionManager create(std::shared_ptr<sf::RenderWindow>& window);

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

};

#endif