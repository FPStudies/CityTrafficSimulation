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


namespace Elements {

/**
 * @brief ensures that new elements are drawn and added to graphs
 * 
 */
class Manager: protected Utils::DoubleKeyManager<Draw::DrawID, std::string, ::Elements::Element>{
    using Inher = Utils::DoubleKeyManager<Draw::DrawID, std::string, ::Elements::Element>;
    using ElementID = Draw::DrawID;

    Draw::Manager& draw_manager_;

    /**
     * @brief vehicle routes graph
     * 
     */
    CityGraph::Proxy<ElementID> vehicles_graph_;

    /**
     * @brief pedestrian routes graph
     * 
     */
    CityGraph::Proxy<ElementID> pedestrians_graph_;

    /**
     * @brief is the element a vehicle route?
     * 
     * @param element element to checko
     * @return true it is
     * @return false it isn't
     */
    bool isVehiclePath(const ::Elements::Element& element) const;

    /**
     * @brief is the element a pedestrian route?
     * 
     * @param element element to checko
     * @return true it is
     * @return false it isn't
     */
    bool isPedestrianPath(const ::Elements::Element& element) const;
    
public:
    
    Manager(Draw::Manager& manager);
    ~Manager();
    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    /**
     * @brief add element to be drawn and to graph if applicable
     * 
     * @param screen 
     * @param name 
     * @param layerName 
     * @return true failure
     * @return false success
     */
    bool addElement(const std::shared_ptr<::Elements::Element> screen, const std::string& name, const std::string& layerName);

    Draw::DrawID getElementID(const std::string& name) const;
    std::string getElementName(const Draw::DrawID& ID) const;

    /**
     * @brief delete element by ID
     * 
     * @param ID 
     * @return true 
     * @return false 
     */
    bool remove(const Draw::DrawID& ID);

    /**
     * @brief delete element by name
     * 
     * @param name 
     * @return true 
     * @return false 
     */
    bool remove(const std::string& name);

    /**
     * @brief connect elements of same route type by ID with different traversing cost both ways
     * 
     * @param ID_A 
     * @param ID_B 
     * @param cost_A_B 
     * @param cost_B_A 
     */
    void connect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B, CityGraph::Cost cost_A_B, CityGraph::Cost cost_B_A);

    /**
     * @brief connect elements of same route type by ID with same traversing cost both ways
     * 
     * @param ID_A 
     * @param ID_B 
     * @param cost 
     */
    void connect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B, CityGraph::Cost cost);

    /**
     * @brief connect elements of same route type by name with different traversing cost both ways
     * 
     * @param name_A 
     * @param name_B 
     * @param cost_A_B 
     * @param cost_B_A 
     */
    void connect(const std::string& name_A, const std::string& name_B, CityGraph::Cost cost_A_B, CityGraph::Cost cost_B_A);

    /**
     * @brief connect elements of same route type by name with same traversing cost both ways
     * 
     * @param name_A 
     * @param name_B 
     * @param cost 
     */
    void connect(const std::string& name_A, const std::string& name_B, CityGraph::Cost cost);

    /**
     * @brief disconnect elements of same route type by ID
     * 
     * @param ID_A 
     * @param ID_B 
     */
    void disconnect(const Draw::DrawID& ID_A, const Draw::DrawID& ID_B);

    /**
     * @brief disconnect elements of same route type by name
     * 
     * @param name_A 
     * @param name_B 
     */
    void disconnect(const std::string& name_A, const std::string& name_B);

    /**
     * @brief find shortest path in graph from start to goal using A*
     * 
     * @param start 
     * @param goal 
     * @return std::list<ElementID> 
     */
    std::list<ElementID> findPath(ElementID start, ElementID goal);
};

};

#endif
