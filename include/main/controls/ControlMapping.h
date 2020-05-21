/*
 * ControlMapping.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_CONTROL_MAPPING_H
#define TRAFFIC_SIM_CONTROL_MAPPING_H


#include <SFML/Graphics.hpp>
#include "MouseMapping.h"
#include "KeyboardMapping.h"

class ControlMapping{
    KeyboardControls keyCtrl_;
    MouseControls mouseCtrl_;

    unsigned int translateEvent(const sf::Event& event);

public:
    ControlMapping();
    ~ControlMapping();
    ControlMapping(const ControlMapping&) = delete;
    ControlMapping(ControlMapping&& other);
    ControlMapping& operator=(ControlMapping&& other);

    bool addControl(MouseControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(MouseControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(MouseControls control);

    bool addControl(KeyboardControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(KeyboardControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(KeyboardControls control);

    void trigger(const sf::Event& event);
};



#endif