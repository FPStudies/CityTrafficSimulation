#ifndef UI_EVENTS_CPP
#define UI_EVENTS_CPP

#include "UIEvents.h"

UIEvents::UIEvents() {}

UIEvents::~UIEvents() {}

UIEvents::UIEvents(const UIEvents& other) {}

void UIEvents::addElement(std::shared_ptr<ElementObserver>& element){
    elements.push_back(element);
}

void UIEvents::run(sf::RenderWindow& window, sf::Event& event){
    if(event.type == sf::Event::MouseButtonReleased)
        if(event.mouseButton.button == sf::Mouse::Left){
            for(auto& it : elements){
                if(it->mousePoints()) {
                    it->update(event);
                    //break; // now it can do tricks as having double button to trigger double action.
                    // of course it can be done making another action class.
                }
            }
        }
}

std::unique_ptr<UIEvents> UIEvents::clone() const{
    return std::unique_ptr<UIEvents>(this->clone_impl());
    //return new UIEvents(*this);
}

bool UIEvents::equals(const EventInterface& other) const{
    if(typeid(UIEvents) == typeid(other)) return true;
    return false;
}

UIEvents* UIEvents::clone_impl() const{
    return new UIEvents(*this);
}

#endif