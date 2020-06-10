/*
 * PedestrianCrossing.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_PEDESTRIAN_CROSSING_H
#define TRAFFIC_SIM_PEDESTRIAN_CROSSING_H

#include "StaticElement.h"

namespace Elements {

    /**
     * @brief pedestrian crossing
     * @details a route for both vehicles and pedestrians; has traffic lights
     * 
     */
    class PedestrianCrossing : public StaticElement {

    public:

        PedestrianCrossing(sf::Window& window, const Texture_ptr& texture);
        ~PedestrianCrossing();

    };

}

#endif
