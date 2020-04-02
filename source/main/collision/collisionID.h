#ifndef ZPR_TRAFFIC_SIM_COLLISION_ID_H
#define ZPR_TRAFFIC_SIM_COLLISION_ID_H

#include "../utility/ID.h"

class CollisionID: virtual public ID<CollisionID>{

    friend class CollisionInterface;

    CollisionID(const ID<CollisionID> id)
    : ID<CollisionID>(id)
    {}

public:

};


#endif