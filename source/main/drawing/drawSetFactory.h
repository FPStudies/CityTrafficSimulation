#ifndef DRAW_SET_FACTORY_H
#define DRAW_SET_FACTORY_H

#include <list>
#include <memory>

#include "drawable.h"
#include "../utility/setTemplate.h"

class DrawSetFactory: public SetTemplate<Drawable>{

public:
    DrawSetFactory();
    virtual ~DrawSetFactory();
    DrawSetFactory(const DrawSetFactory& other);
    DrawSetFactory(const std::shared_ptr<Drawable>& obj);

    void drawAll();

    /*
    Here add a new methods that will create objects
    */


};

#endif