#ifndef EVENT_SET_H
#define EVENT_SET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "eventInterface.h"

/**
 * @brief Set used to group events.
 * 
 */
class EventSet{
    std::vector<std::unique_ptr<EventInterface>> events;

public:
    EventSet();
    ~EventSet();
    EventSet(const EventSet& e);
    EventSet(const EventInterface& event);

    /**
     * @brief Add new event object to the set.
     * The event object is copied while adding.
     * 
     * @param event The object that have implemented an event interface.
     * @return true If the operation was unsuccessful. There was already the same event object in the set.
     * @return false Otherwise.
     */
    bool addEvent(const EventInterface& event);

    /**
     * @brief Remove an event from the set.
     * 
     * @param eventObject 
     * @return true If the operation was unsuccessful. This object was not there.
     * @return false Otherwise.
     */
    bool remove(const EventInterface& eventObject);

    /**
     * @brief It will iterate through all event methods that were added.
     * This method do not iterate through all existing events in program through stack. It only
     * runs an events in set. What and when even do is up to developer.
     * 
     * @param event An event that will be proceed.
     * @param window An window where you want to perform operations.
     */
    void checkEventsOccurence(sf::Event& event, sf::RenderWindow& window);

    bool empty() const;

};

#endif