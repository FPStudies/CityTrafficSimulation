#ifndef DRAW_MANAGER_BRIDGE_TO_SETS_H
#define DRAW_MANAGER_BRIDGE_TO_SETS_H

#include <memory>

#include "drawManager.h"
#include "drawSetFactory.h"

/**
 * @brief Class used for sharing private methods without sharing other things.
 * 
 */
class DrawManagerBridgeToSets{
    void add(std::shared_ptr<Drawable>);

    void remove(std::shared_ptr<Drawable>);
};

#endif