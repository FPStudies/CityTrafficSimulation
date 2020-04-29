/*
 * EventSet.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_EVENT_SET_H
#define TRAFFIC_SIM_EVENT_SET_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "EventInterface.h"
#include "../utility/SetTemplate.hpp"

/**
 * @brief Set used to group events.
 * 
 */
class EventSet: public SetTemplate<EventInterface>{

public:
    EventSet();
    virtual ~EventSet();
    EventSet(const EventSet& e);
    EventSet(const std::shared_ptr<EventInterface>& event);

    /**
     * @brief It will iterate through all event methods that were added.
     * This method do not iterate through all existing events in program through stack. It only
     * runs an events in set. What and when even do is up to developer.
     * 
     * @param event An event that will be proceed.
     * @param window An window where you want to perform operations.
     */
    void checkEventsOccurence(sf::Event& event, sf::RenderWindow& window);

};

#endif
