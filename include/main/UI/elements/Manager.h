/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz, Przybysz Filip
 */

#ifndef TRAFFIC_SIM_MAIN_UI_ELEMENTS_MANAGER_H
#define TRAFFIC_SIM_MAIN_UI_ELEMENTS_MANAGER_H

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

#include "AllElements.h"
#include "../../utility/DoubleKeyManager.hpp"
#include "../../draw/Manager.h"
#include "../../graph/Proxy.hpp"


namespace Element {

class Manager: protected Utils::DoubleKeyManager<Draw::DrawID, std::string, ::Element::Element>{
    using Inher = Utils::DoubleKeyManager<Draw::DrawID, std::string, ::Element::Element>;
    using ElementID = Draw::DrawID;

    Draw::Manager& draw_manager_;

    CityGraph::Proxy<ElementID> vehicles_graph_;

    CityGraph::Proxy<ElementID> pedestrians_graph_;

    bool isVehiclePath(const ::Element::Element& element) const;

    bool isPedestrianPath(const ::Element::Element& element) const;
    
public:
    
    Manager(Draw::Manager& manager);
    ~Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;


    bool addElement(const std::shared_ptr<::Element::Element> screen, const std::string& name, const std::string& layerName);

    Draw::DrawID getElementID(const std::string& name) const;
    std::string getElementName(const Draw::DrawID& ID) const;

    bool remove(const Draw::DrawID& ID);
    bool remove(const std::string& name);

    void connect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B, CityGraph::Cost cost_A_B, CityGraph::Cost cost_B_A);
    void connect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B, CityGraph::Cost cost);
    void connect(const std::string& name_A, const std::string& name_B, CityGraph::Cost cost_A_B, CityGraph::Cost cost_B_A);
    void connect(const std::string& name_A, const std::string& name_B, CityGraph::Cost cost);

    void disconnect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B);
    void disconnect(const std::string& name_A, const std::string& name_B);

    std::list<ElementID> findPath(ElementID start, ElementID goal);
};

};

#endif
