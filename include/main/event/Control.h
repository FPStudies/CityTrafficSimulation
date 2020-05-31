/*
 * Control.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_CONTROL_EVENTS_H
#define TRAFFIC_SIM_CONTROL_EVENTS_H

#include <memory>

#include "../controls/ControlMapping.h"
#include "Interface.h"

namespace Event{

    class Control: public Interface{
        std::unique_ptr<ControlSystem::Mapping> ctrlMapping_;

        virtual Control* clone_impl() const override;
    public:
        /**
         * @brief Construct a new Control Events object
         * @details It uses std::move for a unique_ptr.
         * Mapping can be accessed via other function.
         * 
         * @param mapping
         */
        Control(std::unique_ptr<ControlSystem::Mapping>& mapping);
        virtual ~Control();
        Control(const Control& other);

        virtual void run(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<Control> clone() const;
        virtual bool equals(const Interface& other) const override;

        ControlSystem::Mapping& getMapping();
    };


}

#endif