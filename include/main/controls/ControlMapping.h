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

namespace Control{

    class Mapping{
    public:
        class Controls;
    private:
        Keyboard::MappingNormal key_ctrl_;
        Mouse::Mapping mouse_ctrl_;

        int translateEvent(const sf::Event& event);

    public:
        Mapping();
        ~Mapping();
        Mapping(const Mapping& other);
        Mapping(Mapping&& other);
        Mapping& operator=(Mapping&& other);

        bool operator==(const Mapping& other) const;

        bool addControl(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event);
        void addControlFast(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event);
        bool removeControl(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event);
        void removeControlFast(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event);
        void removeControl(Mouse::Controls control);

        bool addControl(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event);
        void addControlFast(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event);
        bool removeControl(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event);
        void removeControlFast(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event);
        void removeControl(Keyboard::Key control);

        void trigger(sf::RenderWindow &window, const sf::Event& event);
    };


    /**
     * @brief Storage for the all types of controls.
     * 
     */
    class KeyContainer{
    public:
        enum class Type: uint8_t{
            Mouse,
            Keyboard
        };

    private:
        int control_;
        Type type_;

    public:
        KeyContainer(Mouse::Controls other);
        KeyContainer(Keyboard::Key other);
        KeyContainer(const KeyContainer& other);
        KeyContainer(KeyContainer&& other);
        KeyContainer& operator=(KeyContainer&& other);
        ~KeyContainer();

        bool operator==(const KeyContainer& other);
        bool operator<(const KeyContainer& other);

        void setMouseControl(Mouse::Controls control);
        void setKeyboardControl(Keyboard::Key control);

        int getControls();
        Type getType();

    };
}

#endif