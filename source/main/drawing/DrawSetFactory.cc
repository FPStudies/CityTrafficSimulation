/*
 * DrawSetFactory.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAW_SET_FACTORY_CC
#define TRAFFIC_SIM_DRAW_SET_FACTORY_CC

#include "DrawSetFactory.h"

DrawSetFactory::DrawSetFactory(DrawManager& manager) 
: drawManager_(manager), SetTemplate<Drawable>()
{}

DrawSetFactory::~DrawSetFactory() {}

DrawSetFactory::DrawSetFactory(DrawManager& manager, const DrawSetFactory& other)
: drawManager_(manager), SetTemplate<Drawable>(other)
{}

DrawSetFactory::DrawSetFactory(DrawManager& manager, const std::shared_ptr<Drawable>& obj)
: drawManager_(manager), SetTemplate<Drawable>(obj)
{}


void DrawSetFactory::drawAll(){
    for(auto& it : objects){
        if(it->canBeDrawn()) it->draw();
    }
}

#endif