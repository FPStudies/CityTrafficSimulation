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

    struct vertex_info {
        std::string name;
        double x;
        double y;
    };

    //type definitions
    typedef double cost;
    typedef adjacency_list<listS, vecS, directedS, vertex_info,
    property<edge_weight_t, cost> > CityGraphList;
    typedef property_map<CityGraphList, edge_weight_t>::type WeightMap;
    typedef property_map<CityGraphList, vertex_info>::type VertexPropertyMap;
    typedef CityGraphList::vertex_descriptor Vertex;
    typedef CityGraphList::edge_descriptor EdgeDescriptor;
    typedef std::pair<int, int> Edge;

    struct location
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
        CostType dx = m_location[m_goal].x - m_location[u].x;
        CostType dy = m_location[m_goal].y - m_location[u].y;
        return ::sqrt(dx * dx + dy * dy);
    }
    private:
    LocMap m_location;
    VertexDescriptor m_goal;
    };


    struct found_goal {}; // exception for termination

    // visitor that terminates when we find the goal
    template <class Vertex>
    class astar_goal_visitor : public boost::default_astar_visitor {
    public:

        astar_goal_visitor(Vertex goal) : m_goal(goal) {};

        template <class Graph>  void examine_vertex(Vertex u, Graph& g) {
            if(u == m_goal)
                throw found_goal();
        }

    private:

        Vertex m_goal;
    };

}

#endif