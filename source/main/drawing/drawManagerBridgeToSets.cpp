#ifndef ZPR_TRAFFIC_SIM_DRAW_MANAGER_BRIDGE_TO_SETS_CPP
#define ZPR_TRAFFIC_SIM_DRAW_MANAGER_BRIDGE_TO_SETS_CPP

#include "drawManagerBridgeToSets.h"

bool DrawManagerBridgeToSets::addEntity(const std::string& layerName, std::shared_ptr<Drawable> entity, DrawManager& drawManager){
    drawManager.addEntity(layerName, entity);
    return true; //compiler workaround
}

bool DrawManagerBridgeToSets::addLayer(const std::string& previousLayerName, const std::string& layerName, DrawManager& drawManager){
    drawManager.addLayer(previousLayerName, layerName);
    return true; //compiler workaround
}

bool DrawManagerBridgeToSets::remove(const std::string& layerName, std::shared_ptr<Drawable> entity, DrawManager& drawManager){
    drawManager.remove(layerName, entity);
    return true; //compiler workaround
}

#endif
