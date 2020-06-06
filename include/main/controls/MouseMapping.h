/*
 * MouseMapping.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MOUSE_MAPPING__H
#define TRAFFIC_SIM_MOUSE_MAPPING__H

#include "MappingTemplate.h"

namespace Control{
namespace Mouse{
    const static unsigned int WHEEL_OFFSET = 5;
    const static unsigned int MOVE_OFFSET = 7;
    const static unsigned int MOUSE_SIZE = 8;

    enum Controls : int{
        ButtonLeft = sf::Mouse::Button::Left,
        ButtonRight = sf::Mouse::Button::Right,
        ButtonMiddle = sf::Mouse::Button::Middle,
        ButtonX1 = sf::Mouse::Button::XButton1,
        ButtonX2 = sf::Mouse::Button::XButton2,

        WheelVertical = sf::Mouse::Wheel::VerticalWheel + WHEEL_OFFSET,
        WheelHorizontal = sf::Mouse::Wheel::HorizontalWheel + WHEEL_OFFSET,

        Move = MOVE_OFFSET
    };

    class Mapping : public MappingTemplate<Controls, Mapping>{       

    };
}
}

#endif
