/*
 * StaticElement.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_STATIC_ELEMENT_H
#define TRAFFIC_SIM_STATIC_ELEMENT_H

#include "../Element.h"

namespace Element {

    class StaticElement : public Element {

    public:

        StaticElement(sf::Window& window, const Texture_ptr& texture);
        ~StaticElement();

    };

}

#endif
