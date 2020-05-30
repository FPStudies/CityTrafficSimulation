

#include "ControlEvents.h"


ControlEvents::ControlEvents(std::unique_ptr<ControlSystem::Mapping>& mapping)
: ctrlMapping_(std::move(mapping))
{}

ControlEvents::~ControlEvents() = default;

ControlEvents::ControlEvents(const ControlEvents& other)
: ctrlMapping_(std::make_unique<ControlSystem::Mapping>(other.ctrlMapping_))
{}

void ControlEvents::run(sf::RenderWindow& window, const sf::Event& event){
    ctrlMapping_->trigger(window, event);
}

std::unique_ptr<ControlEvents> ControlEvents::clone() const{
    return std::make_unique<ControlEvents>(*this);
}

bool ControlEvents::equals(const EventInterface& other) const{
    return typeid(other) == typeid(ControlEvents) &&
        dynamic_cast<const ControlEvents&>(other).ctrlMapping_ == this->ctrlMapping_;
}

ControlSystem::Mapping& ControlEvents::getMapping(){
    return *ctrlMapping_;
}

