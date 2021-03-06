/*
 * ElementManager.cc
 *
 *      Author: Kordowski Mateusz, Przybysz Filip
 */

#include "Manager.h"

using namespace Elements;

Elements::Manager::Manager(Draw::Manager& manager)
: Utils::DoubleKeyManager<Draw::DrawID, std::string, ::Elements::Element>(),
draw_manager_(manager)
{}

Elements::Manager::~Manager() = default;

bool Elements::Manager::isVehiclePath(const ::Elements::Element& element) const {
    return (typeid(element) == typeid(::Elements::Road) || typeid(element) == typeid(::Elements::PedestrianCrossing) || typeid(element) == typeid(::Elements::RoadConnector));
}

bool Elements::Manager::isPedestrianPath(const ::Elements::Element& element) const {
    return (typeid(element) == typeid(::Elements::Pavement) || typeid(element) == typeid(::Elements::PedestrianCrossing) || typeid(element) == typeid(::Elements::PavementConnector));
}

bool Elements::Manager::addElement(const std::shared_ptr<::Elements::Element> element, const std::string& name, const std::string& layerName){
    bool ret =  Inher::add(element, element->getID(), name);
    if(ret)
        return true;

    ret = draw_manager_.addEntity(layerName, element);

    if(ret){
        Inher::remove(element->getID());
        return true;
    }

    //TODO: add elements that vehicles and pedestrians can traverse to graphs and connect
    if (isVehiclePath(*element)) {
        vehicles_graph_.addVertex(element->getID(), {*(element->getID()), getElementName(element->getID()), element->getPosition().x, element->getPosition().y});
    }
    else if (isPedestrianPath(*element)) {
        pedestrians_graph_.addVertex(element->getID(), {*(element->getID()), getElementName(element->getID()), element->getPosition().x, element->getPosition().y});
    }

    return false;
}

Draw::DrawID Elements::Manager::getElementID(const std::string& name) const{
    return Inher::getKeyOne(name);
}

std::string Elements::Manager::getElementName(const Draw::DrawID& ID) const{
    return Inher::getKeyTwo(ID);
}

bool Elements::Manager::remove(const Draw::DrawID& ID){
    if (isVehiclePath( Inher::getVariable(ID) )) {
        vehicles_graph_.removeVertex(ID);
    }
    else if (isPedestrianPath( Inher::getVariable(ID) )) {
        pedestrians_graph_.removeVertex(ID);
    }

    return Inher::remove(ID);
}

bool Elements::Manager::remove(const std::string& name){
    if (isVehiclePath( Inher::getVariable(name) )) {
        vehicles_graph_.removeVertex( Inher::getKeyOne(name) );
    }
    else if (isPedestrianPath( Inher::getVariable(name) )) {
        pedestrians_graph_.removeVertex( Inher::getKeyOne(name) );
    }

    return Inher::remove(name);
}

void Elements::Manager::connect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B, CityGraph::Cost cost_A_B, CityGraph::Cost cost_B_A) {
    if (isVehiclePath( Inher::getVariable(ID_A)) && isVehiclePath( Inher::getVariable(ID_B)) ) {
        vehicles_graph_.connect( std::make_pair(ID_A, ID_B), cost_A_B, cost_B_A);
    }
    else if (isPedestrianPath( Inher::getVariable(ID_A) ) && isPedestrianPath( Inher::getVariable(ID_B) )) {
        pedestrians_graph_.connect( std::make_pair(ID_A, ID_B), cost_A_B, cost_B_A);
    }
}

void Elements::Manager::connect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B, CityGraph::Cost cost) {
    if (isVehiclePath( Inher::getVariable(ID_A)) && isVehiclePath( Inher::getVariable(ID_B)) ) {
        vehicles_graph_.connect( std::make_pair(ID_A, ID_B), cost);
    }
    else if (isPedestrianPath( Inher::getVariable(ID_A) ) && isPedestrianPath( Inher::getVariable(ID_B) )) {
        pedestrians_graph_.connect( std::make_pair(ID_A, ID_B), cost);
    }
}

void Elements::Manager::connect(const std::string& name_A, const std::string& name_B, CityGraph::Cost cost_A_B, CityGraph::Cost cost_B_A) {
    if (isVehiclePath( Inher::getVariable(name_A)) && isVehiclePath( Inher::getVariable(name_B)) ) {
        vehicles_graph_.connect( std::make_pair( Inher::getKeyOne(name_A), Inher::getKeyOne(name_B) ), cost_A_B, cost_B_A);
    }
    else if (isPedestrianPath( Inher::getVariable(name_A) ) && isPedestrianPath( Inher::getVariable(name_B) )) {
        pedestrians_graph_.connect( std::make_pair( Inher::getKeyOne(name_A), Inher::getKeyOne(name_B) ), cost_A_B, cost_B_A);
    }
}

void Elements::Manager::connect(const std::string& name_A, const std::string& name_B, CityGraph::Cost cost) {
    if (isVehiclePath( Inher::getVariable(name_A)) && isVehiclePath( Inher::getVariable(name_B)) ) {
        vehicles_graph_.connect( std::make_pair( Inher::getKeyOne(name_A), Inher::getKeyOne(name_B) ), cost);
    }
    else if (isPedestrianPath( Inher::getVariable(name_A) ) && isPedestrianPath( Inher::getVariable(name_B) )) {
        pedestrians_graph_.connect( std::make_pair( Inher::getKeyOne(name_A), Inher::getKeyOne(name_B) ), cost);
    }
}

void Elements::Manager::disconnect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B) {
    if (isVehiclePath( Inher::getVariable(ID_A)) && isVehiclePath( Inher::getVariable(ID_B)) ) {
        vehicles_graph_.disconnect( std::make_pair(ID_A, ID_B));
    }
    else if (isPedestrianPath( Inher::getVariable(ID_A) ) && isPedestrianPath( Inher::getVariable(ID_B) )) {
        pedestrians_graph_.disconnect( std::make_pair(ID_A, ID_B));
    }
}
    
void Elements::Manager::disconnect(const std::string& name_A, const std::string& name_B) {
    if (isVehiclePath( Inher::getVariable(name_A)) && isVehiclePath( Inher::getVariable(name_B)) ) {
        vehicles_graph_.disconnect( std::make_pair( Inher::getKeyOne(name_A), Inher::getKeyOne(name_B) ));
    }
    else if (isPedestrianPath( Inher::getVariable(name_A) ) && isPedestrianPath( Inher::getVariable(name_B) )) {
        pedestrians_graph_.disconnect( std::make_pair( Inher::getKeyOne(name_A), Inher::getKeyOne(name_B) ));
    }
}
