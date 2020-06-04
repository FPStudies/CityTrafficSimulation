/*
 * StaticElement.h
 *
 *      Author: Przybysz Filip
 */

#include "Element.h"

namespace Elements {

    class StaticElement : public Element {

    public:

        StaticElement(sf::Window& window, const Elements::Texture_ptr& texture);
        ~StaticElement();

    };

}

