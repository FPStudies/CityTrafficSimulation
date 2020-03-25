#ifndef BASIC_EVENTS_H
#define BASIC_EVENTS_H

#include "eventInterface.h"

class BasicEvents: public EventInterface{

public:
    BasicEvents();
    ~BasicEvents();
    BasicEvents(const BasicEvents& event);

    virtual void run(sf::RenderWindow& window, sf::Event& event);
    virtual EventInterface* clone() const;
    virtual bool equals(const EventInterface& other) const;

};

#endif