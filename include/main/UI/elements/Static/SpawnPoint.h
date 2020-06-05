/*
 * SpawnPoint.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_SPAWN_POINT_H
#define TRAFFIC_SIM_SPAWN_POINT_H

#include "StaticElement.h"

namespace Elements {

    class SpawnPoint : public StaticElement {

    public:

        SpawnPoint(sf::Window& window, const Elements::Texture_ptr& texture);
        ~SpawnPoint();

    };

}

#endif