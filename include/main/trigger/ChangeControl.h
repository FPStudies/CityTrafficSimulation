/*
 * TriggerChangeControl.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_CHANGE_CONTROL_H
#define TRAFFIC_SIM_TRIGGER_CHANGE_CONTROL_H

#include <vector>
#include <memory>

#include "Interface.h"
#include "../event/Manager.h"
#include "ChangeControlInterface.h"

namespace Trigger{ 

    class ChangeControl: public Interface{
        Event::Manager& manager_;
        std::vector<std::string> toDisable_;
        std::vector<std::string> toEnable_;
        std::unique_ptr<ChangeControlInterface> triggerToEnable_;
        std::unique_ptr<ChangeControlInterface> triggerToDisable_;

        ChangeControl* clone_impl() const override;

    public:
        /**
         * @brief Construct a new TriggerDragControl object and get the address of the EventManager.
         * It makes copy of TriggerChangeControlInterface.
         * 
         * @param manager 
         */
        ChangeControl(
            Event::Manager& manager, 
            ChangeControlInterface triggerToEnable, 
            ChangeControlInterface triggerToDisable
            );
        virtual ~ChangeControl();
        ChangeControl(const ChangeControl& other);
        ChangeControl(ChangeControl&&);
        ChangeControl& operator=(ChangeControl&&);

        void trigger(sf::RenderWindow& window, std::unique_ptr<Control::KeyContainer>& control, const sf::Event& event) override;
        std::unique_ptr<ChangeControl> clone() const;
        bool equals(const Interface& other) const override;


    };

}

#endif