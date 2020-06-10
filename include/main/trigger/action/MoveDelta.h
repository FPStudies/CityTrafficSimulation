/*
 * MoveDelta.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_TRIGGER_ACTION_MOVE_DELTA_H
#define TRAFFIC_SIM_MAIN_TRIGGER_ACTION_MOVE_DELTA_H

#include <SFML/Window.hpp>
#include <memory>
#include <typeinfo>

#include "Interface.h"
#include "../../interface/Movable.h"

namespace Trigger::Action{
    class MoveDelta: public Interface{
    public:

    private:
        std::shared_ptr<::Interface::Movable> to_move_;
    
        virtual MoveDelta* clone_impl() const override;

    public:
        MoveDelta();
        virtual ~MoveDelta();
        MoveDelta(const MoveDelta& other);
        MoveDelta(const MoveDelta&& other);
        MoveDelta& operator=(MoveDelta&&) = delete;

        virtual void trigger() override;

        std::unique_ptr<MoveDelta> clone() const;

        virtual bool equals(const Interface& other) const override;
    };    

}



#endif