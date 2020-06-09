

#include "specialization/Exit.h"

using namespace Button;

Exit::Exit(sf::Window& window, const Texture_ptr& texture)
: exit_(window), 
    text_(),
    font_(nullptr),
    texture_(texture), 
    states_(&texture->getResource_const()), 
    can_be_drawn_(true)
{
    this->setTexture(&texture->getResource());
    text_.setString("Exit");
    text_.setCharacterSize(34);
    text_.setFillColor(sf::Color::Red);
}

Exit::~Exit() = default;

bool Exit::isButtonChoosed(sf::RenderWindow& window){
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
    target.draw(text_, states_);
}

sf::FloatRect Exit::getLocalBounds() const{
    return this->sf::RectangleShape::getLocalBounds();
}

sf::FloatRect Exit::getGlobalBounds() const{
    return this->sf::RectangleShape::getGlobalBounds();
}

bool Exit::canBeDrawn() const{
    return can_be_drawn_;
}

void Exit::setFont(const std::shared_ptr<Draw::Font::Font>& font){
    font_ = font;
    text_.setFont(font->getResource());
}

void Exit::setPosition(const sf::Vector2f &position){
    sf::RectangleShape::setPosition(position);

    auto bounds_this = this->getGlobalBounds();
    auto bounds_text = text_.getLocalBounds();
    sf::Vector2f button_center(
        position.x + (bounds_this.width / 2) - (bounds_text.width / 2), 
        position.y + (bounds_this.height / 2) - bounds_text.height
        );
    text_.setPosition(button_center);
    
}

void Exit::setSize(const sf::Vector2f &size){
    sf::RectangleShape::setSize(size);
}

void Exit::setTextSize(unsigned int size){
    text_.setCharacterSize(size);
}