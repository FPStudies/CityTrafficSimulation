/*
 * ButtonInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H
#define TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H

#include "../drawing/Drawable.h"

namespace Button{
    class Interface{
        std::shared_ptr<Drawable> toDrawButton_;

    public:
        Interface()
        : toDrawButton_(nullptr)
        {}
        virtual ~Interface() = default;

        virtual void isButtonChoosed(const float posX, const float posY) = 0;

        virtual void actionPressedButton() = 0;
        virtual void actionReleasedButton() = 0;
    };
}




#endif