/*
 * DrawManagerBridgeToSets.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAW_MANAGER_BRIDGE_TO_SETS_CC
#define TRAFFIC_SIM_DRAW_MANAGER_BRIDGE_TO_SETS_CC

#include "DrawManagerBridgeToSets.h"

bool DrawManagerBridgeToSets::addEntity(const std::string& layer_name, std::shared_ptr<Drawable> entity, DrawManager& draw_manager){
    draw_manager.addEntity(layer_name, entity);
    return true; //compiler workaround
}

bool DrawManagerBridgeToSets::addLayer(const std::string& previous_layer_name, const std::string& layer_name, DrawManager& draw_manager){
    draw_manager.addLayer(previous_layer_name, layer_name);
    return true; //compiler workaround
}

bool DrawManagerBridgeToSets::remove(const std::string& layer_name, std::shared_ptr<Drawable> entity, DrawManager& draw_manager){
    draw_manager.remove(layer_name, entity);
    return true; //compiler workaround
}

#endif
