/*
 * Manager.h
 *
 *      Author: Kordowski Mateusz
 */

#ifndef TRAFFIC_SIM_MAIN_UI_ELEMENTS_MANAGER_H
#define TRAFFIC_SIM_MAIN_UI_ELEMENTS_MANAGER_H

#include <map>

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

    Draw::Manager& draw_manager_;

    CityGraph::Proxy<Draw::DrawID> vehicles_graph_;

    CityGraph::Proxy<Draw::DrawID> pedestrians_graph_;
    
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

    //connect

    //findPath(elem_1, elem_2)
};

};

#endif