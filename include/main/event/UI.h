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

#include "Interface.h"
#include "../UI/elements/ElementObserver.h"

namespace Event{

    class UI: virtual public Interface{
        std::vector<std::shared_ptr<ElementObserver>> elements_;

        virtual UI* clone_impl() const override;

    public:
        UI();
        virtual ~UI();
        UI(const UI&);

        void addElement(std::shared_ptr<ElementObserver>& element);

        virtual void run(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<UI> clone() const;
        virtual bool equals(const Interface& other) const override;
    };

}

#endif
