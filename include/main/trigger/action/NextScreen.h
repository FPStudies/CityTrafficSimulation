/*
 * NextScreen.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_TRIGGER_ACTION_NEXT_SCREEN_H
#define TRAFFIC_SIM_MAIN_TRIGGER_ACTION_NEXT_SCREEN_H

#include <SFML/Window.hpp>
#include <memory>
#include <typeinfo>

#include "Interface.h"
#include "../../screen/Loopback.h"


namespace Trigger::Action{

    class NextScreen: public Interface{
        ScreenID screen_ID_;
        Screen::Loopback& loopback_;
    
        virtual NextScreen* clone_impl() const override;

    public:
        NextScreen(const ScreenID& ID);
        virtual ~NextScreen();
        NextScreen(const NextScreen& other);
        NextScreen(const NextScreen&& other);
        NextScreen& operator=(NextScreen&&) = delete;

        virtual void trigger() override;

        std::unique_ptr<NextScreen> clone() const;

        virtual bool equals(const Interface& other) const override;
    };    
}



#endif