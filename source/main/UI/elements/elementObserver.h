#ifndef ZPR_TRAFFIC_SIM_ELEMENT_OBSERVER_H
#define ZPR_TRAFFIC_SIM_ELEMENT_OBSERVER_H

#include <SFML/Graphics.hpp>

class ElementObserver{
public:
    virtual void update(sf::Event event) = 0; // the subject that will run an update will be an event such as mouse click
    virtual ~ElementObserver() {};
    virtual bool overlap(const ElementObserver& object) = 0;
    virtual bool mousePoints() = 0;
};


#endif