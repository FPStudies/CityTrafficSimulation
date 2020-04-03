#ifndef ZPR_TRAFFIC_SIM_SCREEN_INTERFACE_H
#define ZPR_TRAFFIC_SIM_SCREEN_INTERFACE_H

#include <SFML/Graphics.hpp>

#include "screenID.h"

class ScreenInteface{
    ScreenID ID;

public:
    /**
     * @brief It is used to implement the rendering loops or other kind of tasks. Main channel to implement the program actions.
     * @details Main program will nearly always be in the state of screen. The loop will run this method
     * and return the next screen that should be used. If the returned screen ID will be invalid then it will 
     * break loop and starts to end an program.
     * 
     * @param window 
     * @return ScreenID The next identifier of screen that should be used.
     */
    virtual ScreenID run(std::shared_ptr<sf::RenderWindow> & window) = 0;    // it wll return the next screen that should be used

    ScreenInteface()
    : ID(ScreenID::newID())
    {}

    virtual ~ScreenInteface() {}

    ScreenID getID() const{
        return ID;
    }
};


#endif