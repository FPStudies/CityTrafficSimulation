/*
 * UI.cc
 *
 *      Author: Kordowski Mateusz
 */


#include "UI.h"

using namespace Event;

UI::UI() {}

UI::~UI() {}

UI::UI(const UI& other) {}

void UI::addElement(std::shared_ptr<ElementObserver>& element){
    elements_.push_back(element);
}

void UI::run(sf::RenderWindow& window, const sf::Event& event){
    if(event.type == sf::Event::MouseButtonReleased)
        if(event.mouseButton.button == sf::Mouse::Left){
            for(auto& it : elements_){
                if(it->mousePoints()) {
                    it->update(event);
                    //break; // now it can do tricks as having double button to trigger double action.
                    // of course it can be done making another action class.
                }
            }
        }
}

std::unique_ptr<UI> UI::clone() const{
    return std::unique_ptr<UI>(this->clone_impl());
}

bool UI::equals(const Interface& other) const{
    if(typeid(UI) == typeid(other))
        return true;
    return false;
}

UI* UI::clone_impl() const{
    return new UI(*this);
}
