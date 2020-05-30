/*
 * BasicEvents.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_BASIC_EVENTS_H
#define TRAFFIC_SIM_BASIC_EVENTS_H

#include <memory>

#include "EventInterface.h"

/**
 * @brief Basic functionality:
 * @details
 * - closing application with esc key.
 * 
 */
class BasicEvents: virtual public EventInterface{

    virtual BasicEvents* clone_impl() const override;

public:
    BasicEvents();
    virtual ~BasicEvents();
    BasicEvents(const BasicEvents& event);

    virtual void run(sf::RenderWindow& window, const sf::Event& event) override;
    std::unique_ptr<BasicEvents> clone() const;
    virtual bool equals(const EventInterface& other) const override;

};

#endif
