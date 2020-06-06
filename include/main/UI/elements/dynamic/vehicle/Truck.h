/*
 * Truck.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_TRUCK_H
#define TRAFFIC_SIM_TRUCK_H

#include "Vehicle.h"

namespace Element::Vehicle {

    class Truck : public Vehicle {

    public:

        Truck(sf::Window& window, const Texture_ptr& texture);
        ~Truck();

    };

}

#endif
