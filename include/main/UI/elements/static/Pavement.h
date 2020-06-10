/*
 * Pavement.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_PAVEMENT_H
#define TRAFFIC_SIM_PAVEMENT_H

#include "StaticElement.h"
#include "PavementConnector.h"

namespace Elements {

    class PavementConnector;

    class Pavement : public StaticElement {

        std::deque<std::shared_ptr<PavementConnector>> connectors_;

    public:

        Pavement(sf::Window& window, const Texture_ptr& texture);
        ~Pavement();

    };

}

#endif
