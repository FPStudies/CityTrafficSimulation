/*
 * Button.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_BUTTON_H
#define TRAFFIC_SIM_TRIGGER_BUTTON_H


#include <memory>

#include "Interface.h"
#include "../controls/ControlMapping.h"
#include "../UI/buttons/ButtonInterface.h"

namespace Trigger{ 

    class Button: public Interface{
        std::shared_ptr<::Button::Interface> button_;

    private:
        Button* clone_impl() const override;

    public:
        Button(std::shared_ptr<::Button::Interface>& button);
        virtual ~Button();
        Button(const Button& other);
        Button(Button&& other);
        Button& operator=(Button&& other);

        void trigger(sf::RenderWindow& window, std::unique_ptr<Control::KeyContainer>& control, const sf::Event& event) override;
        std::unique_ptr<Button> clone() const;
        bool equals(const Interface& other) const override;


    };
}




#endif