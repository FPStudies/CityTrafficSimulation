

#include "Exit.h"

using namespace Button;

Exit::Exit(sf::Window& window, const Texture_ptr& texture)
: exit_(window), 
    texture_(texture), 
    states_(&texture->getTexture()), 
    can_be_drawn(true)
{}

Exit::~Exit() = default;

bool Exit::isButtonChoosed(const sf::Vector2i& position){
    if(position.x < 20 && position.y < 20) return true;
    return false;
}

void Exit::actionPressedButton(){
    return;
}
void Exit::actionReleasedButton(){
    exit_.trigger();
}

void Exit::draw(sf::RenderTarget& target) const{
    target.draw(*this);
}

sf::FloatRect Exit::getLocalBounds() const{
    return this->getLocalBounds();
}

sf::FloatRect Exit::getGlobalBounds() const{
    return this->getGlobalBounds();
}

bool Exit::canBeDrawn() const{
    return can_be_drawn;
}