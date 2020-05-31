/*
 * ScreenID.cc
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_SCREEN_ID_CC
#define TRAFFIC_SIM_SCREEN_ID_CC

#include "ScreenID.h"

ScreenID::ScreenID(ID<ScreenID> id)
: ID(id)
{}

ScreenID::ScreenID()
: ID()
{}

ScreenID::~ScreenID() = default;

ScreenID::ScreenID(const ScreenID& other)
: ID(other)
{}

#endif