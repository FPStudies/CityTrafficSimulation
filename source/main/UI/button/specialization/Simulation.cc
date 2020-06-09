

#include "specialization/Simulation.h"

using namespace Button;

Simulation::Simulation(sf::Window& window, const Texture_ptr& texture, const ScreenID& nextScreen)
: exit_(window), 
    text_(),
    font_(nullptr),
    texture_(texture), 
    states_(&texture->getResource_const()), 
    can_be_drawn_(true)
{
    text_.setString("Exit");
    text_.setCharacterSize(34);
    text_.setFillColor(sf::Color::Red);
}

Simulation::~Simulation() = default;

bool Simulation::isButtonChoosed(sf::RenderWindow& window){
    return isButtonChoosedDefault(window, this->getGlobalBounds());
}

void Simulation::actionPressedButton(){
    return;
}
void Simulation::actionReleasedButton(){
    exit_.trigger();
}

void Simulation::draw(sf::RenderTarget& target) const{
    target.draw(*this, states_);
    target.draw(text_, states_);
}

sf::FloatRect Simulation::getLocalBounds() const{
    return this->sf::RectangleShape::getLocalBounds();
}

sf::FloatRect Simulation::getGlobalBounds() const{
    return this->sf::RectangleShape::getGlobalBounds();
}

bool Simulation::canBeDrawn() const{
    return can_be_drawn_;
}

void Simulation::setFont(const std::shared_ptr<Draw::Font::Font>& font){
    font_ = font;
    text_.setFont(font->getResource());
}

void Simulation::setPosition(const sf::Vector2f &position){
    sf::RectangleShape::setPosition(position);

    auto bounds_this = this->getGlobalBounds();
    auto bounds_text = text_.getLocalBounds();
    sf::Vector2f button_center(
        position.x + (bounds_this.width / 2) - (bounds_text.width / 2), 
        position.y + (bounds_this.height / 2) - bounds_text.height
        );
    text_.setPosition(button_center);
    
}

void Simulation::setSize(const sf::Vector2f &size){
    sf::RectangleShape::setSize(size);
}

void Simulation::setTextSize(unsigned int size){
    text_.setCharacterSize(size);
}