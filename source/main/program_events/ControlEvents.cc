

#include "ControlEvents.h"


Control::Control(std::unique_ptr<ControlSystem::Mapping>& mapping)
: ctrlMapping_(std::move(mapping))
{}

Control::~Control() = default;

Control::Control(const Control& other)
: ctrlMapping_(std::make_unique<ControlSystem::Mapping>(other.ctrlMapping_))
{}

void Control::run(sf::RenderWindow& window, const sf::Event& event){
    ctrlMapping_->trigger(window, event);
}

std::unique_ptr<Control> Control::clone() const{
    return std::make_unique<Control>(*this);
}

bool Control::equals(const EventInterface& other) const{
    return typeid(other) == typeid(Control) &&
        dynamic_cast<const Control&>(other).ctrlMapping_ == this->ctrlMapping_;
}

ControlSystem::Mapping& Control::getMapping(){
    return *ctrlMapping_;
}

