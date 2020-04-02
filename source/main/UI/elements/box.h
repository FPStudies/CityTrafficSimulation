#ifndef ZPR_TRAFFIC_SIM_BOX_H
#define ZPR_TRAFFIC_SIM_BOX_H

#include <SFML/Graphics.hpp>

class Box{
    sf::RectangleShape rectangle;
    sf::Sprite sprite;

public:
    Box(const uint& width, const uint& height, const uint& posX, const uint& posY);
    Box(const uint& width, const uint& height);
    virtual ~Box();
    Box(const Box&);

    virtual bool setPosition(const uint& posX, const uint& posY);
    virtual void draw();
    sf::Sprite& getSprite() const;

    void setSprite(const sf::Sprite& sprite);
};

#endif