/*
 * Interface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H
#define TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H


#include <SFML/Window.hpp>
#include <vector>

#include "../draw/Drawable.h"

namespace Trigger::Event{
    class Button;
}


namespace Button{
    class Interface{
    protected:
        std::vector<std::weak_ptr<Draw::Drawable>> to_draw_button_;
        std::vector<std::weak_ptr<::Trigger::Event::Button>> trigger_;

    public:
        Interface()
        : to_draw_button_(), trigger_()
        {}
        
        virtual ~Interface() = default;

        void addTrigger(std::shared_ptr<::Trigger::Event::Button> buttonTrigger){
            trigger_.push_back(buttonTrigger);
        }

        virtual bool isButtonChoosed(sf::RenderWindow& window) = 0;

        virtual void actionPressedButton() = 0;
        virtual void actionReleasedButton() = 0;
    };
}




#endif