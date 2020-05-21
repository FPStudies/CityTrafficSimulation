/*
 * MouseMapping.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MOUSE_MAPPING_H
#define TRAFFIC_SIM_MOUSE_MAPPING_H

#include <map>
#include <vector>
#include "../program_events/EventInterface.h"
#include "../trigger_events/TriggerEventInterface.h"
#include <Mouse.hpp>
#include <memory>

enum MouseControls{
    ButtonLeft = sf::Mouse::Button::Left,
    ButtonRight = sf::Mouse::Button::Right,
    ButtonMiddle = sf::Mouse::Button::Middle,
    ButtonX1 = sf::Mouse::Button::XButton1,
    ButtonX2 = sf::Mouse::Button::XButton2,

    WheelVertical = sf::Mouse::Wheel::VerticalWheel + 5,
    WheelHorizontal = sf::Mouse::Wheel::HorizontalWheel + 5,

    Move = 7
};


class MouseMapping{
    std::map<MouseControls, std::vector<std::shared_ptr<TriggerEventInterface>> > mapping_;

public:
    MouseMapping();
    ~MouseMapping();
    MouseMapping(const MouseMapping&) = delete;
    MouseMapping(MouseMapping&& other);
    MouseMapping& operator=(MouseMapping&& other);

    bool addControl(MouseControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(MouseControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(MouseControls control);

    void trigger(MouseControls control);
};



#endif