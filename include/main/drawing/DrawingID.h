/*
 * DrawingID.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_DRAWING_ID_H
#define TRAFFIC_SIM_DRAWING_ID_H

#include "../utility/ID.hpp"

class DrawingID: virtual public Utils::ID<DrawingID>{

    friend class Drawable;

    DrawingID(const ID<DrawingID> id)
    : ID<DrawingID>(id)
    {}

public:
};

#endif
