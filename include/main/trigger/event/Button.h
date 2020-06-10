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

    /**
     * @brief Trigger that is used to trigger the appropriate action of the button.
     * It separates the press action from releasing the button.
     * 
     */
    class Button: public Interface{
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

        /**
         * @brief Connect the button with the event trigger.
         * Trigger can only have one button bu the button can have multiple triggers.
         * 
         * Button have a weak pointer to the trigger because it will rarely need it. The trigger uses button all the time.
         * 
         * @param button 
         * @param thisTrigger 
         * @return true - if connection was not successful.
         * @return false - if connection was successful.
         */
        static bool connect(const std::shared_ptr<::Button::Interface>& button, const std::shared_ptr<Trigger::Event::Button>& thisTrigger);

        void trigger(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<Button> clone() const;
        bool equals(const Interface& other) const override;


    };
}



#endif
