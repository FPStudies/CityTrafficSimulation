#ifndef BASIC_EVENTS_H
#define BASIC_EVENTS_H

#include <memory>

#include "eventInterface.h"
#include "eventInterface.h"

/**
 * @brief Basic functionality:
 * @details
 * - closing application with esc key.
 * 
 */
class BasicEvents: public EventInterface{

    virtual BasicEvents* clone_impl() const override;

public:
    BasicEvents();
    ~BasicEvents();
    BasicEvents(const BasicEvents& event);

    virtual void run(sf::RenderWindow& window, sf::Event& event);
    std::unique_ptr<BasicEvents> clone() const;
    virtual bool equals(const EventInterface& other) const;

};

#endif