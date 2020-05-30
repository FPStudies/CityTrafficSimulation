/*
 * UIEvents.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_UI_EVENTS_H
#define TRAFFIC_SIM_UI_EVENTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "EventInterface.h"
#include "../UI/elements/ElementObserver.h"


class UIEvents: virtual public EventInterface{
    std::vector<std::shared_ptr<ElementObserver>> elements_;

    virtual UIEvents* clone_impl() const override;

public:
    UIEvents();
    virtual ~UIEvents();
    UIEvents(const UIEvents&);

    void addElement(std::shared_ptr<ElementObserver>& element);

    virtual void run(sf::RenderWindow& window, sf::Event& event) override;
    std::unique_ptr<UIEvents> clone() const;
    virtual bool equals(const EventInterface& other) const override;
};

#endif
