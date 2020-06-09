/*
 * GraphUtility.hpp
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_GRAPH_UTILITY_HPP
#define TRAFFIC_SIM_GRAPH_UTILITY_HPP

#include <boost/graph/astar_search.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/graphviz.hpp>
#include <vector>
#include <list>
#include <iostream>
#include <math.h> 

using namespace std;
using namespace boost;

/**
 * @brief namespace for the graph module of the traffic simulator
 * 
 */
namespace CityGraph {
    
    //type definitions for convinience

    /**
     * @brief element's location on map
     * 
     */
    struct Location
    {
    double x_, y_;
    };

    /**
     * @brief route's cost unit
     * 
     */
    typedef int Cost;

    /**
     * @brief vertex bundled attributes
     * 
     */
    struct VertexInfo {
        int id_;
        std::string name_;
        Location location_;
    };

    /**
     * @brief edge bundled attributes
     * 
     */
    struct EdgeInfo {
        Cost cost_;
    };
 
    /**
     * @brief graph representation
     * 
     */
    typedef adjacency_list<listS, vecS, bidirectionalS, VertexInfo,
    EdgeInfo > CityGraphList;
    typedef CityGraphList::vertex_descriptor VertexDescriptor;
    typedef CityGraphList::edge_descriptor EdgeDescriptor;
    typedef std::pair<VertexDescriptor, VertexDescriptor> Edge;
    typedef property_map<CityGraphList, edge_weight_t EdgeInfo::*>::type WeightMap;
    typedef vec_adj_list_vertex_property_map<CityGraphList, const CityGraphList *, Location, const Location &, Location VertexInfo::*> LocationMap;

    /**
     * @brief euclidean distance heuristic function to be used by A*
     * 
     * @tparam Graph graph
     * @tparam CostType edge's weight unit
     * @tparam LocationMap graph's location map
     */
    template <class Graph, class CostType, class LocationMap>
    class DistanceHeuristic : public astar_heuristic<Graph, CostType> {
    public:
        typedef typename graph_traits<Graph>::vertex_descriptor VertexDescriptor;

        /**
         * @brief Construct a new distance heuristic object
         * 
         * @param locations graph's location map
         * @param goal goal for the A* algorithm
         */
        DistanceHeuristic(const LocationMap& locations, const VertexDescriptor& goal) : m_location_(locations), m_goal_(goal) {};

        CostType operator()(VertexDescriptor u) {
            CostType dx = m_location_[m_goal_].x_ - m_location_[u].x_;
            CostType dy = m_location_[m_goal_].y_ - m_location_[u].y_;
            return ::sqrt(dx * dx + dy * dy);
        }

    private:
        LocationMap m_location_;
        VertexDescriptor m_goal_;
    };


    /**
     * @brief exception for A* termination
     * 
     */
    struct found_goal {};

    /**
     * @brief visitor that terminates when A* finds the goal
     * 
     * @tparam Vertex vertex descriptor
     */
    template <class Vertex>
    class AstarGoalVisitor : public boost::default_astar_visitor {
    public:

        /**
         * @brief Construct a new astar goal visitor object
         * 
         * @param goal goal for A* algorithm
         */
        AstarGoalVisitor(Vertex goal) : m_goal_(goal) {};

        /**
         * @brief check if visited vetex is the goal
         * 
         * @tparam Graph graph type
         * @param u current vertex
         * @param g graph
         */
        template <class Graph>  void examine_vertex(Vertex u, Graph& g) {
            if(u == m_goal_)
                throw found_goal();
        }

    private:

        Vertex m_goal_;
    };

}

#endif
