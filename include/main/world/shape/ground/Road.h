/*
 * Road.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_WORLD_SHAPES_GROUND_ROAD_H
#define TRAFFIC_SIM_MAIN_WORLD_SHAPES_GROUND_ROAD_H

#include <SFML/Graphics.hpp>
#include "../../../draw/Texturing.h"

namespace World::Shape::Ground{

class Road: public sf::RectangleShape, public Draw::Drawable{

public:
    virtual void draw(sf::RenderTarget& target) const override;
    virtual sf::FloatRect getLocalBounds() const override;
    virtual sf::FloatRect getGlobalBounds() const override;
    virtual bool canBeDrawn() const override;

    

};

}



#endif
