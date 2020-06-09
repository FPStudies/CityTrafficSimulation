

#include "Background.h"


using namespace Tiles;


Background::Background(const Texture_ptr& texture)
: texture_(texture), states_(&texture->getResource_const()), can_be_drawn_(true)
{
    this->setTexture(&texture->getResource());
}

Background::~Background() = default;

void Background::draw(sf::RenderTarget& target) const{
    target.draw(*this, states_);
}

sf::FloatRect Background::getLocalBounds() const{
    return this->sf::RectangleShape::getLocalBounds();
}

sf::FloatRect Background::getGlobalBounds() const{
    return this->sf::RectangleShape::getGlobalBounds();
}

bool Background::canBeDrawn() const{
    return can_be_drawn_;
}


