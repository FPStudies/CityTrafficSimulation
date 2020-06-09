/*
 * PavementConnector.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_PAVEMENT_CONNECTOR_H
#define TRAFFIC_SIM_PAVEMENT_CONNECTOR_H

#include "StaticElement.h"
#include "Pavement.h"

namespace Element {

    class Pavement;

    class PavementConnector : public StaticElement {

        std::deque<std::weak_ptr<Pavement>> pavements_;

    public:

        PavementConnector(sf::Window& window, const Texture_ptr& texture);
        ~PavementConnector();

    };

}

#endif
