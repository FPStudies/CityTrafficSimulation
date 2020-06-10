
/*
 * BridgeFromTriggerToInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UI_BUTTON_BRIDGE_FROM_TRIGGER_TO_INTERFACE_H
#define TRAFFIC_SIM_MAIN_UI_BUTTON_BRIDGE_FROM_TRIGGER_TO_INTERFACE_H

#include <memory>

#include "Interface.h"

namespace Trigger::Event{
    class Button;
}

namespace Button{

    // TODO it sneeds to be transfered.
    /**
     * @brief bridge used to perform some operation that should be accessed only by Trigger::Event::Button class.
     * 
     */
    class BridgeFromTriggerToInterface{
        friend class ::Trigger::Event::Button;
        
        static void connectTriggerToInterface(const std::shared_ptr<::Button::Interface>& interface, const std::shared_ptr<::Trigger::Event::Button>& trigger){
            interface->addTrigger(trigger);
        }

    };

}


#endif