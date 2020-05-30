/*
 * ControlEvents.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_CONTROL_EVENTS_H
#define TRAFFIC_SIM_CONTROL_EVENTS_H

#include <memory>

#include "../controls/ControlMapping.h"
#include "EventInterface.h"

class ControlEvents: public EventInterface{
    std::unique_ptr<ControlSystem::Mapping> ctrlMapping_;

    virtual ControlEvents* clone_impl() const override;
public:
    /**
     * @brief Construct a new Control Events object
     * @details It uses std::move for a unique_ptr.
     * Mapping can be accessed via other function.
     * 
     * @param mapping
     */
    ControlEvents(std::unique_ptr<ControlSystem::Mapping>& mapping);
    virtual ~ControlEvents();
    ControlEvents(const ControlEvents& other);

    virtual void run(sf::RenderWindow& window, const sf::Event& event) override;
    std::unique_ptr<ControlEvents> clone() const;
    virtual bool equals(const EventInterface& other) const override;

    ControlSystem::Mapping& getMapping();
};

#endif