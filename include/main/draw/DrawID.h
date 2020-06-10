/*
 * DrawID.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_DRAW_DRAW_ID_H
#define TRAFFIC_SIM_MAIN_DRAW_DRAW_ID_H

#include "../utility/ID.hpp"

namespace Draw{

/**
 * @brief An ID that uniquely identifies Drawable objects.
 * This kind of ID only can be comparable with an ID of the same time.
 * 
 */
class DrawID: virtual public Utils::ID<DrawID>{

    friend class Drawable;

    DrawID(const ID<DrawID> id)
    : ID<DrawID>(id)
    {}

public:
    DrawID()// Always State::Invalid
    : ID()
    {}

    virtual ~DrawID() = default;
    DrawID(const DrawID& other)
    : ID(other)
    {}

};

}

#endif
