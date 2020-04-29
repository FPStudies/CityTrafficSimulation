/*
 * Box.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_BOX_H
#define TRAFFIC_SIM_BOX_H

#include <SFML/Graphics.hpp>

class Box{
    sf::RectangleShape rectangle;
    sf::Sprite sprite;

public:
    Box(const uint& width, const uint& height, const uint& pos_X, const uint& pos_Y);
    Box(const uint& width, const uint& height);
    virtual ~Box();
    Box(const Box&);

    virtual bool setPosition(const uint& pos_X, const uint& pos_Y);
    virtual void draw();
    sf::Sprite& getSprite() const;

    void setSprite(const sf::Sprite& sprite);
};

#endif
