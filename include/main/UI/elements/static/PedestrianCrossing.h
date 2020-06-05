/*
 * PedestrianCrossing.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_PEDESTRIAN_CROSSING_H
#define TRAFFIC_SIM_PEDESTRIAN_CROSSING_H

#include "StaticElement.h"

namespace Element {

    class PedestrianCrossing : public StaticElement {

    public:

        PedestrianCrossing(sf::Window& window, const Texture_ptr& texture);
        ~PedestrianCrossing();

    };

}

#endif