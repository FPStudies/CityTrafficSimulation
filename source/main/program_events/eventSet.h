#ifndef EVENT_SET_H
#define EVENT_SET_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "eventInterface.h"

class EventSet{
    std::vector<std::unique_ptr<EventInterface>> events;

public:
    EventSet();
    ~EventSet();
    EventSet(const EventSet& e);
    EventSet(const EventInterface& event);

    /**
     * @brief Add new event object to the manager.
     * The event object is copied while adding.
     * 
     * @details Method to not check if there is the same event in the container because
     * it copy the object and there is no comparison operator possible (classes are not guaranteed to have
     * any member, they exist only to implement methods).
     * 
     * @param event The object that have implemented run method.
     */
    void addEvent(const EventInterface& event);

    bool remove(const EventInterface& eventObject);

    /**
     * @brief It will iterate through all event methods that were added.
     * This method do not iterate through all existing events in program. It only
     * checks if the event can be proceed.
     * 
     * @param event Should already have fetched event on it. 
     */
    void checkEventsOccurence(sf::Event& event, sf::RenderWindow& window);

    bool empty() const;

};

#endif