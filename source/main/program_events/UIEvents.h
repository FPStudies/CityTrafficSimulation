#ifndef UI_EVENTS_H
#define UI_EVENTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "eventInterface.h"
#include "../UI/elements/elementObserver.h"


class UIEvents: public EventInterface{
    std::vector<std::shared_ptr<ElementObserver>> elements;

public:
    UIEvents();
    ~UIEvents();
    UIEvents(const UIEvents&);

    void addElement(std::shared_ptr<ElementObserver>& element);

    virtual void run(sf::RenderWindow& window, sf::Event& event);
    virtual EventInterface* clone() const;
    virtual bool equals(const EventInterface& other) const;
};

#endif