/*
 * Pavement.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_PAVEMENT_H
#define TRAFFIC_SIM_PAVEMENT_H

#include "StaticElement.h"

namespace Elements {

    class Pavement : public StaticElement {

    public:

        Pavement(sf::Window& window, const Elements::Texture_ptr& texture);
        ~Pavement();

    };

}

#endif