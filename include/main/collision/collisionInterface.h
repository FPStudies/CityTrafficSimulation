#ifndef ZPR_TRAFFIC_SIM_COLLISION_INTERFACE_H
#define ZPR_TRAFFIC_SIM_COLLISION_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "collisionID.h"
#include "sensor.h"

class CollisionInterface{

    CollisionID ID;
    
protected:
    Sensor sensor;

public:
    CollisionInterface()
    : ID(CollisionID::newID())
    {}

    virtual ~CollisionInterface() {}

    //virtual sf::FloatRect boundingBox() = 0;

    /*
    Eventually add some other methods as checking collision pixel by pixel, using private pure virtual method.
    */

    virtual void update() = 0;

    inline CollisionID getID() const{
        return ID;
    }

};

#endif