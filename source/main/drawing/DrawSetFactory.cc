/*
 * DrawSetFactory.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAW_SET_FACTORY_CC
#define TRAFFIC_SIM_DRAW_SET_FACTORY_CC

#include "DrawSetFactory.h"

DrawSetFactory::DrawSetFactory(DrawManager& manager) 
: draw_manager_(manager), Utils::SetTemplate<Drawable>()
{}

DrawSetFactory::~DrawSetFactory() {}

DrawSetFactory::DrawSetFactory(DrawManager& manager, const DrawSetFactory& other)
: draw_manager_(manager), Utils::SetTemplate<Drawable>(other)
{}

DrawSetFactory::DrawSetFactory(DrawManager& manager, const std::shared_ptr<Drawable>& obj)
: draw_manager_(manager), Utils::SetTemplate<Drawable>(obj)
{}


void DrawSetFactory::drawAll(){
    for(auto& it : objects_){
        if(it->canBeDrawn())
            it->draw();
    }
}

#endif