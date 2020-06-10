/*
 * Pedestrian.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_PEDESTRIAN_H
#define TRAFFIC_SIM_PEDESTRIAN_H

#include "DynamicElement.h"

namespace Elements {

    class Pedestrian : public DynamicElement {

    public:

        Pedestrian(sf::Window& window, const Texture_ptr& texture);
        ~Pedestrian();

    };

}

#endif
