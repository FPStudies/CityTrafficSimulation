/*
 * StaticElement.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_STATIC_ELEMENT_H
#define TRAFFIC_SIM_STATIC_ELEMENT_H

#include "../Element.h"

#include <deque>

namespace Elements {

    /**
     * @brief base class for map elements
     * @details those objects are edited on map between simulations and stay there during simulations
     * 
     */
    class StaticElement : public Element {

    public:

        StaticElement(sf::Window& window, const Texture_ptr& texture);
        ~StaticElement();

    };

}

#endif
