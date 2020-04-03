#ifndef ZPR_TRAFFIC_SIM_SCREEN_ID_H
#define ZPR_TRAFFIC_SIM_SCREEN_ID_H

#include <limits.h>
#include <memory>

#include "../utility/ID.h"

class ScreenID : public ID<ScreenID>{

/**
 * @brief This is used to prevent other derived classes to have an control over private constructor.
 * This class is mean only to be inherited by ScreenInterface class.
 * 
 */
friend class ScreenInteface;

private:
    ScreenID(ID<ScreenID> id);

public:

    ScreenID();// Always State::Invalid
    virtual ~ScreenID();
    ScreenID(const ScreenID& other);
};

#endif