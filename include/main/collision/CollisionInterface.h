/*
 * CollisionInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_COLLISION_INTERFACE_H
#define TRAFFIC_SIM_COLLISION_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <Box2d/Box2d.h>

#include "CollisionID.h"
#include "Sensor.h"

class CollisionInterface{

    CollisionID ID_;
    
protected:
    Sensor sensor_;

public:
    CollisionInterface()
    : ID_(CollisionID::newID())
    {}

    virtual ~CollisionInterface() {}

    //virtual sf::FloatRect boundingBox() = 0;

    /*
    Eventually add some other methods as checking collision pixel by pixel, using private pure virtual method.
    */

    virtual void update() = 0;

    inline CollisionID getID() const{
        return ID_;
    }

};

#endif
