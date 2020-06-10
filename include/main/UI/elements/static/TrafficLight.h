/*
 * TrafficLight.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_TRAFFIC_LIGHT_H
#define TRAFFIC_SIM_TRAFFIC_LIGHT_H

#include "StaticElement.h"
#include <chrono>

namespace Elements {

    /**
     * @brief traffic light class
     * @details helps with realistic moving logic for dynamic elements
     * 
     */
    class TrafficLight : public StaticElement {

    /**
     * @brief traffic light colours
     * 
     */
    enum class Light {RED, YELLOW, GREEN};

    /**
     * @brief light duration units
     * 
     */
    using Interval = std::chrono::duration<int, std::centi>;

    /**
     * @brief current colour
     * 
     */
    Light light_state_;

    /**
     * @brief colour change interval
     * 
     */
    Interval light_change_interval_;

    public:

        TrafficLight(sf::Window& window, const Texture_ptr& texture);
        ~TrafficLight();

    };

}

#endif
