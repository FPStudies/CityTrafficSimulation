/*
 * EventInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_EVENT_INTERFACE_CPP
#define TRAFFIC_SIM_EVENT_INTERFACE_CPP

#include <SFML/Graphics.hpp>
#include <memory>

class EventInterface{
    virtual EventInterface* clone_impl() const = 0;

public:
    EventInterface() {};
    virtual ~EventInterface() {};

    /**
     * @brief Do some action based on the event.
     * 
     * @param window Where the event was fetched.
     * @param event Fetched event.
     */
    virtual void run(sf::RenderWindow& window, sf::Event& event) = 0;

    /**
     * @brief Simple method to copy object.
     * Return the same object type as your higher class.
     * 
     * @return EventInterface* 
     */
    std::unique_ptr<EventInterface> clone() const{
        return std::unique_ptr<EventInterface>(this->clone_impl());
    }

    /**
     * @brief Method to check if the two events are the same.
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    virtual bool equals(const EventInterface& other) const = 0;

    EventInterface(const EventInterface&) = delete;
    EventInterface(const EventInterface&&) = delete;

};

#endif
