

#include "Default.h"

using namespace Button;

Default::Default(sf::Window& window, const Texture_ptr& texture)
: action_triggers_pressed_(),
action_triggers_released_(),
    text_(),
    font_(nullptr),
    texture_(texture), 
    states_(&texture->getResource_const()), 
    can_be_drawn_(true)
{
    this->setTexture(&texture->getResource());
}

Default::~Default() = default;

bool Default::isButtonChoosed(sf::RenderWindow& window){
    return isButtonChoosedDefault(window, this->getGlobalBounds());
}

void Default::actionPressedButton(){
    for(auto& it : action_triggers_pressed_){
        it->trigger();
    }
}
void Default::actionReleasedButton(){
    for(auto& it : action_triggers_released_){
        it->trigger();
    }
}

void Default::draw(sf::RenderTarget& target) const{
    target.draw(*this, states_);
    target.draw(text_, states_);
}

sf::FloatRect Default::getLocalBounds() const{
    return this->sf::RectangleShape::getLocalBounds();
}

sf::FloatRect Default::getGlobalBounds() const{
    return this->sf::RectangleShape::getGlobalBounds();
}

bool Default::canBeDrawn() const{
    return can_be_drawn_;
}

void Default::setFont(const std::shared_ptr<Draw::Font::Font>& font){
    font_ = font;
    text_.setFont(font->getResource());
}

void Default::setPosition(const sf::Vector2f &position){
    sf::RectangleShape::setPosition(position);

    auto bounds_this = this->getGlobalBounds();
    auto bounds_text = text_.getLocalBounds();
    sf::Vector2f button_center(
        position.x + (bounds_this.width / 2) - (bounds_text.width / 2), 
        position.y + (bounds_this.height / 2) - bounds_text.height
        );
    text_.setPosition(button_center);
    
}

void Default::setSize(const sf::Vector2f &size){
    sf::RectangleShape::setSize(size);
}

void Default::setTextSize(unsigned int size){
    text_.setCharacterSize(size);
}

Draw::Font::Font& Default::getFont(){
    return *font_;
}

sf::Text& Default::getText(){
    return text_;
}

void Default::addTriggerOnPressed(const std::shared_ptr<Trigger::Action::Interface>& trigger){
    action_triggers_pressed_.push_back(trigger);
}

void Default::addTriggerOnReleased(const std::shared_ptr<Trigger::Action::Interface>& trigger){
    action_triggers_released_.push_back(trigger);
}