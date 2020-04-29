/*
 * CollisionManagerBridgeToSets.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_COLLISION_MANAGER_BRIDGE_TO_SETS_H
#define TRAFFIC_SIM_COLLISION_MANAGER_BRIDGE_TO_SETS_H

#include <memory>

#include "CollisionManager.h"

class CollisionManagerBridgeToSets{
    friend class DrawSetFactory;

private:
    void addEntity(std::shared_ptr<CollisionInterface>& entity, CollisionManager& manager);

    bool remove(std::shared_ptr<CollisionInterface>& entity, CollisionManager& manager);

};

#endif
