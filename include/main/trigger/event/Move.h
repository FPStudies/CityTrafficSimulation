/*
 * TriggerMovable.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_TRIGGER_MOVABLE_H
#define TRAFFIC_SIM_TRIGGER_MOVABLE_H

#include "Interface.h"
#include "../../actions/Movable.h"

#include <memory>

namespace Trigger{ 
namespace Event{

    class Move: public Interface{

        std::shared_ptr<Movable> toDrag_;

        Move* clone_impl() const override;

    public:
        Move(const std::shared_ptr<Movable>& object);
        virtual ~Move();
        Move(const Move&) = delete;
        Move(Move&&);
        Move& operator=(Move&&);

        void trigger(sf::RenderWindow& window, const sf::Event& event) override;
        std::unique_ptr<Move> clone() const;
        bool equals(const Interface& other) const override;


    };

}}

#endif