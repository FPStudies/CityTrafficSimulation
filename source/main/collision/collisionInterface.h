#ifndef COLLISION_INTERFACE_H
#define COLLISION_INTERFACE_H

#include <SFML/Graphics.hpp>

#include "collisionID.h"

class CollisionInterface{
    using BitType = uint;

    CollisionID ID;
    BitType bitMask;

protected:

    inline void setBitMask(const BitType& mask){
        bitMask = mask;
    }

public:
    CollisionInterface()
    : ID(CollisionID::newID())
    {}

    virtual ~CollisionInterface() {}

    virtual sf::FloatRect boundingBox() = 0;

    /*
    Eventually add some other methods as checking collision pixel by pixel, using private pure virtual method.
    */

    inline CollisionID getID() const{
        return ID;
    }

    inline const BitType& getBitMask(){
        return bitMask;
    }
    
};

#endif