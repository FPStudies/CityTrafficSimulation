/*
 * Vehicle.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_VEHICLE_H
#define TRAFFIC_SIM_VEHICLE_H

#include "../DynamicElement.h"

namespace Elements::Vehicle {

    class Vehicle : public DynamicElement {

    public:

        Vehicle(sf::Window& window, const Texture_ptr& texture);
        ~Vehicle();

    };

}

#endif
