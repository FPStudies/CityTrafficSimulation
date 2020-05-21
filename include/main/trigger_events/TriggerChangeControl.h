/*
 * TriggerChangeControl.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_CHANGE_CONTROL_H
#define TRAFFIC_SIM_TRIGGER_CHANGE_CONTROL_H

#include <vector>
#include <memory>

#include "TriggerEventInterface.h"
#include "../program_events/EventManager.h"
#include "TriggerChangeControlInterface.h"

class TriggerChangeControl: public TriggerEventInterface{
    /*
    * Plain pointer but it should not be triggered outside of event manager.
    */
    EventManager* manager_;
    std::vector<std::string> toDisable_;
    std::vector<std::string> toEnable_;
    std::unique_ptr<TriggerChangeControlInterface> triggerToEnable_;
    std::unique_ptr<TriggerChangeControlInterface> triggerToDisable_;

    TriggerChangeControl* clone_impl() const override;

public:
    /**
     * @brief Construct a new TriggerDragControl object and get the address of the EventManager.
     * It makes copy of TriggerChangeControlInterface.
     * 
     * @param manager 
     */
    TriggerChangeControl(EventManager manager, TriggerChangeControlInterface triggerToEnable, TriggerChangeControlInterface triggerToDisable);
    virtual ~TriggerChangeControl();
    TriggerChangeControl(const TriggerChangeControl& other);
    TriggerChangeControl(TriggerChangeControl&&);
    TriggerChangeControl& operator=(TriggerChangeControl&&);

    void trigger(sf::RenderWindow& window, ControlMapping& control) override;
    std::unique_ptr<TriggerChangeControl> clone() const;
    bool equals(const TriggerEventInterface& other) const override;


};

#endif