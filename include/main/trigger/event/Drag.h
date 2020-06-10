/*
 * Drag.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_TRIGGER_EVENT_DRAG_H
#define TRAFFIC_SIM_MAIN_TRIGGER_EVENT_DRAG_H


#include <memory>

#include "Interface.h"
#include "../../interface/Movable.h"

namespace Trigger::Event{ 

    class Drag: public Interface{
        std::shared_ptr<::Interface::Movable> to_move_;
        bool was_pressed_;

    private:
        Drag* clone_impl() const override;

    public:
        Drag();
        virtual ~Drag();
        Drag(const Drag& other);
        Drag(Drag&& other);
        Drag& operator=(Drag&& other);

        void trigger(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<Drag> clone() const;
        bool equals(const Interface& other) const override;


    };
}




#endif