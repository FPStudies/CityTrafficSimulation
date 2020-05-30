/*
 * EventInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_EVENT_INTERFACE_H
#define TRAFFIC_SIM_TRIGGER_EVENT_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controls/ControlMapping.h"


namespace Trigger{
    /**
     * @brief Events that are triggered by other means.
     * They are not present in the main loop but the main loop can trigger them.
     * 
     */
    class EventInterface{
        virtual EventInterface* clone_impl() const = 0;

    public:
        EventInterface() {};
        virtual ~EventInterface() {};
        EventInterface(const EventInterface&) = delete;
        EventInterface(const EventInterface&&) {};

        virtual void trigger(sf::RenderWindow& window, std::unique_ptr<ControlSystem::Controls>& control, const sf::Event& event) = 0;

        std::unique_ptr<EventInterface> clone() const{
            return std::unique_ptr<EventInterface>(this->clone_impl());
        }

        virtual bool equals(const EventInterface& other) const = 0;
    };    
}




#endif