/*
 * TriggerMovable.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_MOVABLE_H
#define TRAFFIC_SIM_TRIGGER_MOVABLE_H

#include "TriggerEventInterface.h"
#include "../actions/Movable.h"

#include <memory>

class TriggerMovable: public TriggerEventInterface{

    std::shared_ptr<Movable> toDrag_;

    TriggerMovable* clone_impl() const override;

public:
    TriggerMovable(const std::shared_ptr<Movable>& object);
    virtual ~TriggerMovable();
    TriggerMovable(const TriggerMovable&) = delete;
    TriggerMovable(TriggerMovable&&);
    TriggerMovable& operator=(TriggerMovable&&);

    void trigger(sf::RenderWindow& window, ControlMapping& control) override;
    std::unique_ptr<TriggerMovable> clone() const;
    bool equals(const TriggerEventInterface& other) const override;


};


#endif