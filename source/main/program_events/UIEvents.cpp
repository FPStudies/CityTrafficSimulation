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
                if(it->mousePoints()) it->update(event);
            }
        }
}

EventInterface* UIEvents::clone() const{
    return new UIEvents(*this);
}

bool UIEvents::equals(const EventInterface& other) const{
    if(typeid(UIEvents) == typeid(other)) return true;
    return false;
}

#endif