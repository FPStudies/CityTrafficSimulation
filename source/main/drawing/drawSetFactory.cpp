#ifndef ZPR_TRAFFIC_SIM_DRAW_SET_FACTORY_CPP
#define ZPR_TRAFFIC_SIM_DRAW_SET_FACTORY_CPP

#include "drawSetFactory.h"

DrawSetFactory::DrawSetFactory(DrawManager& manager) 
: drawManager(manager), SetTemplate<Drawable>()
{}

DrawSetFactory::~DrawSetFactory() {}

DrawSetFactory::DrawSetFactory(DrawManager& manager, const DrawSetFactory& other)
: drawManager(manager), SetTemplate<Drawable>(other)
{}

DrawSetFactory::DrawSetFactory(DrawManager& manager, const std::shared_ptr<Drawable>& obj)
: drawManager(manager), SetTemplate<Drawable>(obj)
{}


void DrawSetFactory::drawAll(){
    for(auto& it : objects){
        if(it->canBeDrawn()) it->draw();
    }
}

#endif