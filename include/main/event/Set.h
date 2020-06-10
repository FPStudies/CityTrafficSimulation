/*
 * Set.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_EVENT_SET_H
#define TRAFFIC_SIM_MAIN_EVENT_SET_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "Interface.h"
#include "ToggleInterface.h"
#include "../utility/SetTemplate.hpp"

namespace Event{

    /**
     * @brief Set used to group events. It can be passed to the Event::Manager
     * 
     */
    class Set: public Utils::SetTemplate<Interface>{

    public:
        Set();
        virtual ~Set();
        Set(const Set& e);
        Set(const std::shared_ptr<Interface>& event);

        /**
         * @brief It will iterate through all event methods that were added to this set.
         * What and when even do is up to developer.
         * 
         * @param event An event that will be proceed.
         * @param window An window where you want to perform operations.
         */
        void checkEventsOccurence(sf::Event& event, sf::RenderWindow& window);

        /**
         * @brief It will iterate through all event methods that were added to this set.
         * What and when even do is up to developer.
         * It is used by ToggleInterface event to toggle some events in specified manager.
         * 
         * @param event 
         * @param window 
         * @param manager - Event::Manager where the events to toggle are.
         */
        void checkToggleOccurence(sf::Event& event, sf::RenderWindow& window, Manager& manager);
    };

}

#endif
