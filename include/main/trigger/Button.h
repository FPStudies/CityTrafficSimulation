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

    class Button: public Interface, public std::enable_shared_from_this<Button>{
        std::shared_ptr<::Button::Interface> button_;

    private:
        Button* clone_impl() const override;
        Button();

    public:
        /**
         * @brief Create an Trigger::Button object.
         * 
         * @return std::shared_ptr<Button> - returned Trigger::Button object
         */
        static std::shared_ptr<Button> create();
        virtual ~Button();
        Button(const Button& other);
        Button(Button&& other);
        Button& operator=(Button&& other);

        bool connect(std::shared_ptr<::Button::Interface>& button);

        void trigger(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<Button> clone() const;
        bool equals(const Interface& other) const override;


    };
}




#endif