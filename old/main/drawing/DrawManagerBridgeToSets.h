/*
 * DrawManagerBridgeToSets.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAW_MANAGER_BRIDGE_TO_SETS_H
#define TRAFFIC_SIM_DRAW_MANAGER_BRIDGE_TO_SETS_H

#include <memory>

#include "DrawManager.h"
#include "DrawSetFactory.h"

/**
 * @brief Class used for sharing private methods without sharing other things.
 * 
 */
class DrawManagerBridgeToSets{

    friend class DrawSetFactory;

private:

    static bool addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity, DrawManager& draw_manager);

    static bool addLayer(const std::string& previous_layer_name, const std::string& layer_name, DrawManager& draw_manager);

    static bool remove(const std::string& layer_name, std::shared_ptr<Drawable> entity, DrawManager& draw_manager);
};

#endif
