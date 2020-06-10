/*
 * ExitWindow.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_TRIGGER_ACTION_EXIT_WINDOW_H
#define TRAFFIC_SIM_MAIN_TRIGGER_ACTION_EXIT_WINDOW_H

#include <SFML/Window.hpp>
#include <memory>
#include <typeinfo>

#include "../../screen/ScreenInterface.h"
#include "Interface.h"


namespace Trigger::Action{

    class ExitWindow: public Interface{
        sf::Window& window_;
    
        virtual ExitWindow* clone_impl() const override;

    public:
        ExitWindow(sf::Window& window);
        virtual ~ExitWindow();
        ExitWindow(const ExitWindow& other);
        ExitWindow(const ExitWindow&& other);
        ExitWindow& operator=(ExitWindow&&) = delete;

        virtual void trigger() override;

        std::unique_ptr<ExitWindow> clone() const;

        virtual bool equals(const Interface& other) const override;
    };    
}



#endif
