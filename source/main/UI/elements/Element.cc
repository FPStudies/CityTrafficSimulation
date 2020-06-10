/*
 * Element.cc
 *
 *      Author: Przybysz Filip, Kordowski Mateusz
 */

#include "Element.h"

Elements::Element::Element(sf::Window& window, const Texture_ptr& texture)
:   texture_(texture), 
    states_(&texture->getResource_const()),
    can_be_drawn_(true)
{}

Elements::Element::~Element() = default;

void Elements::Element::draw(sf::RenderTarget& target) const{
    target.draw(*this, states_);
}

sf::FloatRect Elements::Element::getLocalBounds() const{
    return this->sf::RectangleShape::getLocalBounds();
}

sf::FloatRect Elements::Element::getGlobalBounds() const{
    return this->sf::RectangleShape::getGlobalBounds();
}

bool Elements::Element::canBeDrawn() const{
    return can_be_drawn_;
}

void Elements::Element::setPosition(const sf::Vector2f &position){
    sf::RectangleShape::setPosition(position);

    auto bounds_this = this->getGlobalBounds();
    sf::Vector2f element_center(
        position.x + (bounds_this.width / 2), 
        position.y + (bounds_this.height / 2)
        );
    
}

void Elements::Element::setSize(const sf::Vector2f &size){
    sf::RectangleShape::setSize(size);
}
