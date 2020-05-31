/*
 * ToggleInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_EVENT_TOGGLE_INTERFACE_H
#define TRAFFIC_SIM_MAIN_EVENT_TOGGLE_INTERFACE_H

#include <memory>

#include "../controls/ControlMapping.h"
#include "Interface.h"
#include <typeinfo>

namespace Event{

    class Manager;

    class ToggleInterface: public Interface{
        virtual ToggleInterface* clone_impl() const = 0;

        // unused
        virtual void run(sf::RenderWindow& window, const sf::Event& event) override
        {}

    protected:
        Manager& manager_;
        
    public:

        ToggleInterface(Manager& manager)
        : Interface(), manager_(manager)
        {}
        
        virtual ~ToggleInterface() = default;
        ToggleInterface(const ToggleInterface& other) = delete;

        virtual Type getType() const override{
            return Type::Toggle;
        }

        virtual void run(sf::RenderWindow& window, const sf::Event& event, Manager& manager) = 0;
        std::unique_ptr<ToggleInterface> clone() const{
            return std::unique_ptr<ToggleInterface>(this->clone_impl());
        }
        virtual bool equals(const ToggleInterface& other) const = 0;
    };


}

#endif