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

namespace CityGraph {

    struct VertexInfo {
        std::string name;
        double x;
        double y;
    };

    //type definitions
    typedef double cost;
    typedef adjacency_list<listS, vecS, directedS, vertex_info,
    property<edge_weight_t, cost> > CityGraphList;
    typedef property_map<CityGraphList, edge_weight_t>::type WeightMap;
    typedef property_map<CityGraphList, VertexInfo>::type VertexPropertyMap;
    typedef CityGraphList::vertex_descriptor Vertex;
    typedef CityGraphList::edge_descriptor EdgeDescriptor;
    typedef std::pair<int, int> Edge;

    struct Location
    {
    double x, y;
    };

    // euclidean distance heuristic
    template <class Graph, class CostType, class LocMap>
    class distance_heuristic : public astar_heuristic<Graph, CostType>
    {
    public:
    typedef typename graph_traits<Graph>::vertex_descriptor VertexDescriptor;
    distance_heuristic(LocMap l, VertexDescriptor goal)
        : m_location(l), m_goal(goal) {}
    CostType operator()(VertexDescriptor u)
    {
        CostType dx = m_location_[m_goal_].x - m_location_[u].x;
        CostType dy = m_location_[m_goal_].y - m_location_[u].y;
        return ::sqrt(dx * dx + dy * dy);
    }
    private:
    LocMap m_location_;
    VertexDescriptor m_goal_;
    };


    struct found_goal {}; // exception for termination

    // visitor that terminates when we find the goal
    template <class Vertex>
    class astar_goal_visitor : public boost::default_astar_visitor {
    public:

        astar_goal_visitor(Vertex goal) : m_goal_(goal) {};

        template <class Graph>  void examine_vertex(Vertex u, Graph& g) {
            if(u == m_goal_)
                throw found_goal();
        }

    private:

        Vertex m_goal_;
    };

}

#endif