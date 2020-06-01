/*
 * TriggerChangeControlInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_CHANGE_CONTROL_INTERFACE_H
#define TRAFFIC_SIM_TRIGGER_CHANGE_CONTROL_INTERFACE_H

#include "../controls/ControlMapping.h"

namespace Trigger{ 

    class ChangeControlInterface{

    public:
        /**
         * @brief Used to find if specific kind of event occurred.
         * 
         * @return true 
         * @return false 
         */
        virtual bool isTriggered(Control::Mapping& control) = 0;
    };

}

#endif