/*
 * ButtonInterface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H
#define TRAFFIC_SIM_GAME_BUTTON_INTERFACE_H


#include <SFML/Window.hpp>
#include "../drawing/Drawable.h"

class Trigger::Button;

namespace Button{
    class Interface{
    protected:
        std::shared_ptr<Drawable> to_draw_button_;
        std::weak_ptr<Trigger::Button> trigger_;

    public:
        Interface()
        : to_draw_button_(nullptr), trigger_()
        {}
        virtual ~Interface() = default;

        void setTrigger(std::shared_ptr<Trigger::Button> buttonTrigger){
            trigger_ = buttonTrigger;
        }

        virtual bool isButtonChoosed(const sf::Vector2i& position) = 0;

        virtual void actionPressedButton() = 0;
        virtual void actionReleasedButton() = 0;
    };
}




#endif