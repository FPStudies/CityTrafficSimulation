/*
 * Graph.cc
 *
 *      Author: Przybysz Filip
 */

#include "Graph.h"
#include "GraphUtility.hpp"

using namespace CityGraph;

Graph::Graph(): is_build_(false) {};

const bool Graph::isBuild() const {
    return is_build_;
}

void Graph::buildGraph(long number_of_vertices, const std::vector<Edge>& edges, const std::vector<double>& weights) {
    city_graph_ = CityGraphList(number_of_vertices);

    //TODO: add vertices properties

    for (unsigned int i=0; i<edges.size(); ++i) {
        EdgeDescriptor e; bool inserted;
        boost::tie(e, inserted) = add_edge(edges[i].first, edges[i].second, city_graph_);
        weights_[e] = weights[i];
    }

    is_build_ = true;
}

std::list<CityGraph::Vertex> Graph::findShortestPath (Vertex& start, Vertex& goal) const{

    vector<Vertex> p(num_vertices(city_graph_));
    vector<cost> d(num_vertices(city_graph_));

    try {
    // call astar named parameter interface
    astar_search_tree (city_graph_, start, distance_heuristic<CityGraphList, cost, VertexPropertyMap> (vertices_, goal),
       predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, city_graph_))).
       distance_map(make_iterator_property_map(d.begin(), get(vertex_index, city_graph_))).
       visitor(astar_goal_visitor<Vertex>(goal)));
    } 
  catch(found_goal fg) { // found a path to the goal
    list<Vertex> shortest_path;
    for(Vertex v = goal;; v = p[v]) {
      shortest_path.push_front(v);
      if(p[v] == v)
        break;
    }
    return shortest_path;
  }

}