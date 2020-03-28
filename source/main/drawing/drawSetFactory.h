#ifndef DRAW_SET_FACTORY_H
#define DRAW_SET_FACTORY_H

#include <list>
#include <memory>

#include "drawable.h"
#include "../utility/setTemplate.h"
#include "drawManager.h"

class DrawSetFactory: public SetTemplate<Drawable>{
    friend class DrawManagerBridgeToSets;

    /**
     * @brief Used to store all dawable objects from window.
     * Decide, what should be rendered on a given frame.
     * 
     */
    DrawManager& drawManager;

public:
    DrawSetFactory(DrawManager& manager);
    virtual ~DrawSetFactory();
    DrawSetFactory(DrawManager& manager, const DrawSetFactory& other);
    DrawSetFactory(DrawManager& manager, const std::shared_ptr<Drawable>& obj);

    void drawAll();

    /*
    Here add a new methods that will create objects
    */


};

#endif