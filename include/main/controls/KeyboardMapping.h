/*
 * KeyboardMapping.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_KEYBOARD_MAPPING_H
#define TRAFFIC_SIM_KEYBOARD_MAPPING_H


#include <map>
#include <vector>
#include <memory>
#include "../program_events/EventInterface.h"
#include "Keyboard.hpp"

typedef sf::Keyboard::Key KeyboardControls;

class KeyboardMapping{
    std::map<KeyboardControls, std::vector<std::shared_ptr<TriggerEventInterface>> > mapping_;
public:
    KeyboardMapping();
    ~KeyboardMapping();
    KeyboardMapping(const KeyboardMapping&) = delete;
    KeyboardMapping(KeyboardMapping&& other);
    KeyboardMapping& operator=(KeyboardMapping&& other);

    bool addControl(KeyboardControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(KeyboardControls control, const std::shared_ptr<TriggerEventInterface>& event);
    bool removeControl(KeyboardControls control);

    void trigger(KeyboardControls control);
};



#endif