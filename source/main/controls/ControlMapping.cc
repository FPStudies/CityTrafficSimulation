
#include "ControlMapping.h"

using namespace ControlSystem;

Mapping::Mapping()
: keyCtrl_(), mouseCtrl_()
{}

Mapping::~Mapping() = default;

Mapping::Mapping(Mapping&& other)
: keyCtrl_(std::move(other.keyCtrl_)), mouseCtrl_(std::move(other.mouseCtrl_))
{}

Mapping& Mapping::operator=(Mapping&& other){
    keyCtrl_ = std::move(other.keyCtrl_);
    mouseCtrl_ = std::move(other.mouseCtrl_);
}

int Mapping::translateEvent(const sf::Event& event){
    switch(event.type){
        case sf::Event::KeyPressed :
        case sf::Event::KeyReleased :
            return event.key.code;

        case sf::Event::MouseWheelScrolled :
            return event.mouseWheelScroll.wheel + Mouse::WHEEL_OFFSET;
        case sf::Event::MouseButtonPressed :
        case sf::Event::MouseButtonReleased :
            return event.mouseButton.button;
        case sf::Event::MouseMoved :
        case sf::Event::MouseEntered :
        case sf::Event::MouseLeft :
            return Mouse::MOVE_OFFSET;     

        default:
            return -1;       
    }
}

bool Mapping::addControl(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event){
    mouseCtrl_.addControl(control, event);
}

bool Mapping::addControlFast(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event){
    mouseCtrl_.addControlFast(control, event);
}

bool Mapping::removeControl(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event){
    mouseCtrl_.removeControl(control, event);
}

bool Mapping::removeControlFast(Mouse::Controls control, const std::shared_ptr<TriggerEventInterface>& event){
    mouseCtrl_.removeControlFast(control, event);
}

bool Mapping::removeControl(Mouse::Controls control){
    mouseCtrl_.removeControl(control);
}


bool Mapping::addControl(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event){
    keyCtrl_.addControl(control, event);
}

bool Mapping::addControlFast(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event){
    keyCtrl_.addControlFast(control, event);
}

bool Mapping::removeControl(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event){
    keyCtrl_.removeControl(control, event);
}

bool Mapping::removeControlFast(Keyboard::Key control, const std::shared_ptr<TriggerEventInterface>& event){
    keyCtrl_.removeControlFast(control, event);
}

bool Mapping::removeControl(Keyboard::Key control){
    keyCtrl_.removeControl(control);
}

void Mapping::trigger(sf::RenderWindow &window, const sf::Event& event){
    int ret = translateEvent(event);
    if(ret == -1) throw std::runtime_error("Trigger cannot interpret event");

    if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased){
        std::unique_ptr<ControlSystem::Controls> newControl(std::make_unique<ControlSystem::Controls>(static_cast<Keyboard::Key>(ret)));
        keyCtrl_.trigger(window, static_cast<Keyboard::Key>(ret), newControl, event);
    }
    else{
        std::unique_ptr<ControlSystem::Controls> newControl(std::make_unique<ControlSystem::Controls>(static_cast<Mouse::Controls>(ret)));
        mouseCtrl_.trigger(window, static_cast<Mouse::Controls>(ret), newControl, event);
    }
}



Controls::Controls(Mouse::Controls other)
: control_(other), type_(Type::Mouse)
{}

Controls::Controls(Keyboard::Key other)
: control_(other), type_(Type::Keyboard)
{}

Controls::~Controls() = default;

void Controls::setMouseControl(Mouse::Controls control){
    control_ = control;
    type_ = Type::Mouse;
}
void Controls::setKeyboardControl(Keyboard::Key control){
    control_ = control;
    type_ = Type::Keyboard;
}

int Controls::getControls(){
    return control_;
}

Controls::Type Controls::getType(){
    return type_;
}

