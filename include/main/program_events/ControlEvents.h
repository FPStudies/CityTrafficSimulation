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

    std::unique_ptr<ControlMapping> ctrlMapping_;

    virtual ControlEvents* clone_impl() const override;
public:

    ControlEvents();
    ~ControlEvents();
    ControlEvents(const ControlEvents& event);

    virtual void run(sf::RenderWindow& window, sf::Event& event) override;
    std::unique_ptr<ControlEvents> clone() const;
    virtual bool equals(const EventInterface& other) const override;

};

#endif