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
    return false;
}

Draw::DrawID Element::Manager::getElementID(const std::string& name) const{
    return Inher::getKeyOne(name);
}

std::string Element::Manager::getElementName(const Draw::DrawID& ID) const{
    return Inher::getKeyTwo(ID);
}

bool Element::Manager::remove(const Draw::DrawID& ID){
    return Inher::remove(ID);
}

bool Element::Manager::remove(const std::string& name){
    return Inher::remove(name);
}