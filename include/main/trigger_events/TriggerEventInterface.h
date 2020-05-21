/*
 * TriggerEventInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_EVENT_INTERFACE_H
#define TRAFFIC_SIM_TRIGGER_EVENT_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controls/ControlMapping.h"

/**
 * @brief Events that are triggered by other means.
 * They are not present in the main loop but the main loop can trigger them.
 * 
 */
class TriggerEventInterface{
    virtual TriggerEventInterface* clone_impl() const = 0;

public:
    TriggerEventInterface() {};
    virtual ~TriggerEventInterface() {};
    TriggerEventInterface(const TriggerEventInterface&) = delete;
    TriggerEventInterface(const TriggerEventInterface&&) {};

    virtual void trigger(sf::RenderWindow& window, ControlMapping& control) = 0;

    std::unique_ptr<TriggerEventInterface> clone() const{
        return std::unique_ptr<TriggerEventInterface>(this->clone_impl());
    }

    virtual bool equals(const TriggerEventInterface& other) const = 0;
};



#endif