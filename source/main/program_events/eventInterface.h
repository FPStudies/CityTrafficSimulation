#ifndef EVENT_INTERFACE_CPP
#define EVENT_INTERFACE_CPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class EventInterface{
public:
    EventInterface() {};
    virtual ~EventInterface() {};

    /**
     * @brief This will run once. Checks event and perform some action.
     * 
     * @param window where the event was fetched.
     * @param event fetched event 
     */
    virtual void run(sf::RenderWindow& window, sf::Event& event) = 0;

    /**
     * @brief Simple method to copy object.
     * Return the same object type as your higher class
     * 
     * @return EventInterface* 
     */
    virtual EventInterface* clone() const = 0;

    /**
     * @brief Method to check if the two of events are the same/
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