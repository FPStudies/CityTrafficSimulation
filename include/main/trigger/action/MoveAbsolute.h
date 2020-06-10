/*
 * MoveAbsolute.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_TRIGGER_ACTION_MOVE_ABSOLUTE_H
#define TRAFFIC_SIM_MAIN_TRIGGER_ACTION_MOVE_ABSOLUTE_H

#include <SFML/Window.hpp>
#include <memory>
#include <typeinfo>

#include "Interface.h"
#include "../../interface/Movable.h"

namespace Trigger::Action{


    class MoveAbsolute: public Interface{
    public:

    private:
        std::shared_ptr<::Interface::Movable> to_move_;
    
        virtual MoveAbsolute* clone_impl() const override;

    public:
        MoveAbsolute();
        virtual ~MoveAbsolute();
        MoveAbsolute(const MoveAbsolute& other);
        MoveAbsolute(const MoveAbsolute&& other);
        MoveAbsolute& operator=(MoveAbsolute&&) = delete;

        virtual void trigger() override;

        std::unique_ptr<MoveAbsolute> clone() const;

        virtual bool equals(const Interface& other) const override;
    };    

}



#endif