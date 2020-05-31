/*
 * Interface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_EVENT_INTERFACE_H
#define TRAFFIC_SIM_TRIGGER_EVENT_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <typeinfo>


namespace Control{
    class Mapping;
    class KeyContainer;    
}



namespace Trigger{
    /**
     * @brief Events that are triggered by other means.
     * They are not present in the main loop but the main loop can trigger them.
     * 
     */
    class Interface{
    private:
        virtual Interface* clone_impl() const = 0;

    public:
        Interface() = default;
        virtual ~Interface() = default;
        Interface(const Interface&) = delete;
        Interface(const Interface&&) {};

        virtual void trigger(sf::RenderWindow& window, const sf::Event& event) = 0;

        std::unique_ptr<Interface> clone() const{
            return std::unique_ptr<Interface>(this->clone_impl());
        }

        virtual bool equals(const Interface& other) const = 0;
    };    
}




#endif