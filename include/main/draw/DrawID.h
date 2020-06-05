/*
 * DrawID.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAWING_ID_H
#define TRAFFIC_SIM_DRAWING_ID_H

#include "../utility/ID.hpp"

namespace Draw{

class DrawID: virtual public Utils::ID<DrawID>{

    friend class Drawable;

    DrawID(const ID<DrawID> id)
    : ID<DrawID>(id)
    {}

public:
};

}

#endif
