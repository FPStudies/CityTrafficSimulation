/*
 * Button.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_BUTTON_H
#define TRAFFIC_SIM_TRIGGER_BUTTON_H

#include "EventInterface.h"
#include <memory>
#include "../UI/buttons/ButtonInterface.h"

namespace Trigger{ 

    class Button: public EventInterface{
        std::unique_ptr<::Button::Interface> button_;


        Button* clone_impl() const override;

    public:
        Button();
        virtual ~Button();
        Button(const Button&) = delete;
        Button(Button&&);
        Button& operator=(Button&&);

        void trigger(sf::RenderWindow& window, std::unique_ptr<ControlSystem::Controls>& control, const sf::Event& event) override;
        std::unique_ptr<Button> clone() const;
        bool equals(const EventInterface& other) const override;


    };
}




#endif