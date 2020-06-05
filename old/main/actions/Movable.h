/*
 * Movable.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MOVABLE_H
#define TRAFFIC_SIM_MOVABLE_H

class Movable{

public:
    virtual bool move(const float& pos_X, const float& pos_Y) = 0;
};

#endif