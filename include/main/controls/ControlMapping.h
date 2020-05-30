/*
 * ControlMapping.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_CONTROL_MAPPING_H
#define TRAFFIC_SIM_CONTROL_MAPPING_H


#include <SFML/Graphics.hpp>
#include "MouseMapping.h"
#include "KeyboardMappingNormal.h"

namespace ControlSystem{

    class Mapping{
    public:
        class Controls;
    private:
        Keyboard::MappingNormal keyCtrl_;
        Mouse::Mapping mouseCtrl_;

        int translateEvent(const sf::Event& event);

    public:
        Mapping();
        ~Mapping();
        Mapping(const Mapping& other);
        Mapping(Mapping&& other);
        Mapping& operator=(Mapping&& other);

        bool operator==(const Mapping& other) const;

        bool addControl(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event);
        bool addControlFast(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event);
        bool removeControl(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event);
        bool removeControlFast(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event);
        bool removeControl(Mouse::Controls control);

        bool addControl(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event);
        bool addControlFast(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event);
        bool removeControl(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event);
        bool removeControlFast(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event);
        bool removeControl(Keyboard::Key control);

        void trigger(sf::RenderWindow &window, const sf::Event& event);
    };


    /**
     * @brief Storage for the all types of controls.
     * 
     */
    class Controls{
    public:
        enum class Type: uint8_t{
            Mouse,
            Keyboard
        };

    private:
        int control_;
        Type type_;

    public:
        Controls(Mouse::Controls other);
        Controls(Keyboard::Key other);
        Controls(const Controls& other);
        Controls(Controls&& other);
        Controls& operator=(Controls&& other);
        ~Controls();

        bool operator==(const Controls& other);
        bool operator<(const Controls& other);

        void setMouseControl(Mouse::Controls control);
        void setKeyboardControl(Keyboard::Key control);

        int getControls();
        Type getType();

    };
}

#endif