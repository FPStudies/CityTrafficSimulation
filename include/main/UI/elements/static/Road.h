/*
 * Road.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_ROAD_H
#define TRAFFIC_SIM_ROAD_H

#include "StaticElement.h"

namespace Elements {

    class Road : public StaticElement {

    public:

        Road(sf::Window& window, const Elements::Texture_ptr& texture);
        ~Road();

    };

}

#endif
