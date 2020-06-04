

#include "Exit.h"

using namespace Button;

Exit::Exit(sf::Window& window, const Texture_ptr& texture)
: exit_(window), 
    texture_(texture), 
    states_(&texture->getResource_const()), 
    can_be_drawn(true)
{}

Exit::~Exit() = default;

bool Exit::isButtonChoosed(sf::RenderWindow& window){
    auto bounds = this->getGlobalBounds();
    return isButtonChoosedDefault(window, this->getGlobalBounds());
}

void Exit::actionPressedButton(){
    return;
}
void Exit::actionReleasedButton(){
    exit_.trigger();
}

void Exit::draw(sf::RenderTarget& target) const{
    target.draw(*this, states_);
}

sf::FloatRect Exit::getLocalBounds() const{
    return this->sf::RectangleShape::getLocalBounds();
}

sf::FloatRect Exit::getGlobalBounds() const{
    return this->sf::RectangleShape::getGlobalBounds();
}

bool Exit::canBeDrawn() const{
    return can_be_drawn;
}