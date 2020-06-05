
#include "ControlMapping.h"

Control::Mapping::Mapping()
: key_ctrl_(), mouse_ctrl_()
{}

Control::Mapping::~Mapping() = default;

Control::Mapping::Mapping(Mapping&& other)
: key_ctrl_(std::move(other.key_ctrl_)), mouse_ctrl_(std::move(other.mouse_ctrl_))
{}

Control::Mapping::Mapping(const Mapping& other)
: key_ctrl_(other.key_ctrl_), mouse_ctrl_(other.mouse_ctrl_)
{}

Control::Mapping& Control::Mapping::operator=(Mapping&& other){
    key_ctrl_ = std::move(other.key_ctrl_);
    mouse_ctrl_ = std::move(other.mouse_ctrl_);
    return *this;
}

bool Control::Mapping::operator==(const Mapping& other) const{
    return key_ctrl_ == other.key_ctrl_ && mouse_ctrl_ == other.mouse_ctrl_;
}

int Control::Mapping::translateEvent(const sf::Event& event){
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

bool Control::Mapping::addControl(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event){
    return mouse_ctrl_.addControl(control, event);
}

void Control::Mapping::addControlFast(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event){
    mouse_ctrl_.addControlFast(control, event);
}

bool Control::Mapping::removeControl(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event){
    return mouse_ctrl_.removeControl(control, event);
}

void Control::Mapping::removeControlFast(Mouse::Controls control, const std::shared_ptr<Trigger::Event::Interface>& event){
    mouse_ctrl_.removeControlFast(control, event);
}

void Control::Mapping::removeControl(Mouse::Controls control){
    mouse_ctrl_.removeControl(control);
}


bool Control::Mapping::addControl(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event){
    return key_ctrl_.addControl(control, event);
}

void Control::Mapping::addControlFast(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event){
    key_ctrl_.addControlFast(control, event);
}

bool Control::Mapping::removeControl(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event){
    return key_ctrl_.removeControl(control, event);
}

void Control::Mapping::removeControlFast(Keyboard::Key control, const std::shared_ptr<Trigger::Event::Interface>& event){
    key_ctrl_.removeControlFast(control, event);
}

void Control::Mapping::removeControl(Keyboard::Key control){
    key_ctrl_.removeControl(control);
}

void Control::Mapping::trigger(sf::RenderWindow &window, const sf::Event& event){
    int ret = translateEvent(event);
    if(ret == -1) return;//throw std::runtime_error("Trigger cannot interpret event");d

    if(event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased){
        key_ctrl_.trigger(window, static_cast<Keyboard::Key>(ret), event);
    }
    else{
        mouse_ctrl_.trigger(window, static_cast<Mouse::Controls>(ret), event);
    }
}



Control::KeyContainer::KeyContainer(Mouse::Controls other)
: control_(other), type_(Type::Mouse)
{}

Control::KeyContainer::KeyContainer(Keyboard::Key other)
: control_(other), type_(Type::Keyboard)
{}

Control::KeyContainer::~KeyContainer() = default;

Control::KeyContainer::KeyContainer(const KeyContainer& other)
: control_(other.control_), type_(other.type_)
{}

Control::KeyContainer::KeyContainer(KeyContainer&& other)
: control_(other.control_), type_(other.type_)
{}

Control::KeyContainer& Control::KeyContainer::operator=(Control::KeyContainer&& other){
    control_ = other.control_;
    type_ = other.type_;
    return *this;
}

bool Control::KeyContainer::operator==(const Control::KeyContainer& other){
    if(type_ != other.type_ || control_ != other.control_) 
        return false;
    return true;
}

bool Control::KeyContainer::operator<(const Control::KeyContainer& other){
    if(control_ < other.control_) 
        return true;
    return false;
}

void Control::KeyContainer::setMouseControl(Mouse::Controls control){
    control_ = control;
    type_ = Type::Mouse;
}
void Control::KeyContainer::setKeyboardControl(Keyboard::Key control){
    control_ = control;
    type_ = Type::Keyboard;
}

int Control::KeyContainer::getControls(){
    return control_;
}

Control::KeyContainer::Type Control::KeyContainer::getType(){
    return type_;
}

