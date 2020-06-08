/*
 * Button.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_TRIGGER_EVENT_BUTTON_H
#define TRAFFIC_SIM_MAIN_TRIGGER_EVENT_BUTTON_H


#include <memory>

#include "Interface.h"
#include "../../controls/ControlMapping.h"
#include "../../UI/button/Interface.h"
#include "../../UI/button/BridgeFromTriggerToInterface.h"

namespace Trigger::Event{ 

    class Button: public Interface, public std::enable_shared_from_this<Button>{
        friend class BridgeToTrigger;
        std::shared_ptr<::Button::Interface> button_;
        bool was_pressed_;

    private:
        Button* clone_impl() const override;
        Button();

        bool connectWith(const std::shared_ptr<::Button::Interface>& button);

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

        static bool connect(const std::shared_ptr<::Button::Interface>& button, const std::shared_ptr<Trigger::Event::Button>& thisTrigger);

        void trigger(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<Button> clone() const;
        bool equals(const Interface& other) const override;


    };
}




#endif