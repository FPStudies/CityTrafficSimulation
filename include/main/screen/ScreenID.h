/*
 * ScreenID.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_SCREEN_SCREEN_ID_H
#define TRAFFIC_SIM_MAIN_SCREEN_SCREEN_ID_H

#include <limits.h>
#include <memory>

#include "../utility/ID.hpp"

/**
 * @brief ID used to differentiate the screens.
 * 
 */
class ScreenID : public Utils::ID<ScreenID>{

/**
 * @brief This is used to prevent other derived classes to have an control over private constructor.
 * This class is mean only to be inherited by ScreenInterface class.
 * 
 */
friend class ScreenInterface;

private:
    ScreenID(ID<ScreenID> id);

public:

    ScreenID();// Always State::Invalid
    virtual ~ScreenID();
    ScreenID(const ScreenID& other);
};

#endif
