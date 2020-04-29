/*
 * DrawSetFactory.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAW_SET_FACTORY_H
#define TRAFFIC_SIM_DRAW_SET_FACTORY_H

#include <list>
#include <memory>

#include "Drawable.h"
#include "../utility/SetTemplate.hpp"
#include "DrawManager.h"
#include "DrawManagerBridgeToSets.h"

class DrawSetFactory: public SetTemplate<Drawable>{
    //friend class DrawManagerBridgeToSets;
    //friend class CollisionManagerBridgeToSets;

    using Bridge = DrawManagerBridgeToSets;

    /**
     * @brief Used to store all dawable objects from window.
     * Decide, what should be rendered on a given frame.
     * 
     */
    DrawManager& draw_manager_;

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
