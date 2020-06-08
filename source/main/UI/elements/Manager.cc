/*
 * ElementManager.cc
 *
 *      Author: Kordowski Mateusz
 */

#include "Manager.h"

using namespace Element;

Element::Manager::Manager(Draw::Manager& manager)
: Utils::DoubleKeyManager<Draw::DrawID, std::string, ::Element::Element>(),
draw_manager_(manager)
{}

Element::Manager::~Manager() = default;

bool Element::Manager::addElement(const std::shared_ptr<::Element::Element> element, const std::string& name, const std::string& layerName){
    bool ret =  Inher::add(element, element->getID(), name);
    if(ret)
        return true;

    ret = draw_manager_.addEntity(layerName, element);

    if(ret){
        Inher::remove(element->getID());
        return true;
    }

    //TODO: add roads and pavements to graphs and connect (are ids unique? even between element types?)
    if (typeid(element) == typeid(::Element::Road)){
        vehicles_graph_.addVertex({*(element->getID()), getElementName(element->getID()), element->getPosition().x, element->getPosition().y});
    }
    else if (typeid(element) == typeid(::Element::Pavement) || typeid(element) == typeid(::Element::PedestrianCrossing)){
        pedestrians_graph_.addVertex({*(element->getID()), getElementName(element->getID()), element->getPosition().x, element->getPosition().y});
    }

    return false;
}

Draw::DrawID Element::Manager::getElementID(const std::string& name) const{
    return Inher::getKeyOne(name);
}

std::string Element::Manager::getElementName(const Draw::DrawID& ID) const{
    return Inher::getKeyTwo(ID);
}

bool Element::Manager::remove(const Draw::DrawID& ID){
    //TODO:remove from graph
    return Inher::remove(ID);
}

bool Element::Manager::remove(const std::string& name){
    //TODO:remove from graph
    return Inher::remove(name);
}