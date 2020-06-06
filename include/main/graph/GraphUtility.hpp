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
    
    //type definitions
    struct Location
    {
    double x, y;
    };
    typedef int Cost;

    struct VertexInfo {
        int id;
        std::string name;
        Location location;
    };
    struct EdgeInfo {
        Cost cost;
    };
 
    typedef adjacency_list<listS, vecS, bidirectionalS, VertexInfo,
    EdgeInfo > CityGraphList;
    typedef CityGraphList::vertex_descriptor VertexDescriptor;
    typedef CityGraphList::edge_descriptor EdgeDescriptor;
    typedef CityGraphList::vertices_size_type VertexNumber;
    typedef std::pair<VertexNumber, VertexNumber> Edge;
    typedef property_map<CityGraphList, edge_weight_t EdgeInfo::*>::type WeightMap;
    typedef vec_adj_list_vertex_property_map<CityGraphList, const CityGraphList *, Location, const Location &, Location VertexInfo::*> LocationMap;
    
    

    // euclidean distance heuristic
    template <class Graph, class CostType, class LocationMap>
    class distance_heuristic : public astar_heuristic<Graph, CostType> {
    public:
        typedef typename graph_traits<Graph>::vertex_descriptor VertexDescriptor;

        distance_heuristic(const LocationMap& l, const VertexDescriptor& goal) : m_location_(l), m_goal_(goal) {};

        CostType operator()(VertexDescriptor u) {
            CostType dx = m_location_[m_goal_].x - m_location_[u].x;
            CostType dy = m_location_[m_goal_].y - m_location_[u].y;
            return ::sqrt(dx * dx + dy * dy);
        }

    private:
        LocationMap m_location_;
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
