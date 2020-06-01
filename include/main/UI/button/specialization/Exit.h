/*
 * Exit.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_SPECIALIZATION_EXIT_H
#define TRAFFIC_SIM_GAME_BUTTON_SPECIALIZATION_EXIT_H

#include <SFML/Window.hpp>
#include <iostream>

#include "../Interface.h"
#include "../../../trigger/action/ExitWindow.h"

namespace Button{
    class Exit: public ::Button::Interface{
        Trigger::Action::ExitWindow exit_;

    public:
        Exit(sf::Window& window);
        virtual ~Exit();

        virtual bool isButtonChoosed(const sf::Vector2i& position) override;

        virtual void actionPressedButton() override;
        virtual void actionReleasedButton() override;
    };
}




#endif