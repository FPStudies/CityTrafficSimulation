/*
 * Interface.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UI_BUTTON_INTERFACE_H
#define TRAFFIC_SIM_MAIN_UI_BUTTON_INTERFACE_H


#include <SFML/Window.hpp>
#include <vector>

#include "../draw/Drawable.h"

namespace Trigger::Event{
    class Button;
}


namespace Button{

    /**
     * @brief Interface of a button.
     * 
     */
    class Interface{
        friend class BridgeFromTriggerToInterface;

        void addTrigger(std::shared_ptr<::Trigger::Event::Button> button_trigger){
            trigger_.push_back(button_trigger);
        }

    protected:
        std::vector<std::weak_ptr<Draw::Drawable>> to_draw_button_;
        std::vector<std::weak_ptr<::Trigger::Event::Button>> trigger_;

        bool isButtonChoosedDefault(sf::RenderWindow& window, const sf::FloatRect& global_bounds){
            auto pixel_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            
            if(
                global_bounds.left <= pixel_coords.x && 
                global_bounds.top <= pixel_coords.y && 
                global_bounds.left + global_bounds.width > pixel_coords.x &&
                global_bounds.top + global_bounds.height > pixel_coords.y
                ){
                return true;
            }

            return false;
        }

    public:
        Interface()
        : to_draw_button_(), trigger_()
        {}
        
        virtual ~Interface() = default;      

        virtual bool isButtonChoosed(sf::RenderWindow& window) = 0;

        virtual void actionPressedButton() = 0;
        virtual void actionReleasedButton() = 0;
    };

    /**
     * @brief Interface of a button with inherited Drawable.
     * 
     */
    class InterfaceDraw: public Interface, public Draw::Drawable{
        
    };

    /**
     * @brief Interface of a button with inherited Drawable and Transformable.
     * 
     */
    class InterfaceDrawTrans: public InterfaceDraw, public sf::Transformable{
        
    };
}


#endif
