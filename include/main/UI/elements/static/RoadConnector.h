/*
 * RoadConnector.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_ROAD_CONNECTOR_H
#define TRAFFIC_SIM_ROAD_CONNECTOR_H

#include "StaticElement.h"
#include "Road.h"

namespace Elements {

    class Road;

    class RoadConnector : public StaticElement {

        std::deque<std::weak_ptr<Road>> roads_;

    public:

        RoadConnector(sf::Window& window, const Texture_ptr& texture);
        ~RoadConnector();

    };

}

#endif
