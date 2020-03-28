#ifndef SCREEN_ID_CPP
#define SCREEN_ID_CPP

#include "screenID.h"

ScreenID::ScreenID(ID<ScreenID> id)
: ID(id)
{}

ScreenID::ScreenID()
: ID()
{}

ScreenID::~ScreenID() {}

ScreenID::ScreenID(const ScreenID& other)
: ID(other)
{}

#endif