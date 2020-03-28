#ifndef DRAW_SET_FACTORY_CPP
#define DRAW_SET_FACTORY_CPP

#include "drawSetFactory.h"

DrawSetFactory::DrawSetFactory() 
: SetTemplate<Drawable>()
{}

DrawSetFactory::~DrawSetFactory() {}

DrawSetFactory::DrawSetFactory(const DrawSetFactory& other)
: SetTemplate<Drawable>(other)
{}

DrawSetFactory::DrawSetFactory(const std::shared_ptr<Drawable>& obj)
: SetTemplate<Drawable>(obj)
{}


void DrawSetFactory::drawAll(){
    for(auto& it : objects){
        if(it->canBeDrawn()) it->draw();
    }
}

#endif