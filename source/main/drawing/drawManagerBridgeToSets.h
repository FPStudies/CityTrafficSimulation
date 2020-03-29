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

    friend class DrawSetFactory;

private:

    static bool addEntity(const std::string& layerName, std::shared_ptr<Drawable> entity, DrawManager& drawManager);

    static bool addLayer(const std::string& previousLayerName, const std::string& layerName, DrawManager& drawManager);

    static bool remove(const std::string& layerName, std::shared_ptr<Drawable> entity, DrawManager& drawManager);
};

#endif