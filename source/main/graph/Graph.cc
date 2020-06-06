/*
 * Graph.cc
 *
 *      Author: Przybysz Filip
 */

#include "Graph.h"
#include "GraphUtility.hpp"

using namespace CityGraph;

Graph::Graph() {
  city_graph_ = CityGraphList(0);
};


VertexDescriptor Graph::addVertex(VertexInfo vertex_info) {
  VertexDescriptor vertex = add_vertex(city_graph_);
  city_graph_[vertex] = vertex_info;
  return vertex;
}

VertexInfo Graph::getVertex(VertexDescriptor vertex) {
  return city_graph_[vertex];
}

EdgeInfo Graph::getEdge(EdgeDescriptor edge) {
  return city_graph_[edge];
}


std::pair<EdgeDescriptor, EdgeDescriptor> Graph::addEdge(Edge edge, std::pair<Cost, Cost> costs) {
  EdgeDescriptor edge_1, edge_2;
  bool inserted_1, inserted_2;

  boost::tie(edge_1, inserted_1) = add_edge(edge.first, edge.second, city_graph_);
  city_graph_[edge_1].cost = costs.first;
  boost::tie(edge_2, inserted_2) = add_edge(edge.second, edge.first, city_graph_);
  city_graph_[edge_2].cost = costs.second;

  return std::make_pair(edge_1, edge_2);
}


void Graph::buildGraph(const std::vector<VertexInfo>& vertex_info, const std::vector<Edge>& edges, const std::vector<Cost>& weights) {
    city_graph_ = CityGraphList(0);

    //add vertices
    for (unsigned int i=0; i<vertex_info.size(); ++i) {
        addVertex(vertex_info[i]);
    }

    //add edges
    for (unsigned int i=0; i<edges.size(); ++i) {
        EdgeDescriptor edge;
        bool inserted;
        boost::tie(edge, inserted) = add_edge(edges[i].first, edges[i].second, city_graph_);
        city_graph_[edge].cost = weights[i];
    }
}


std::list<CityGraph::VertexDescriptor> Graph::findShortestPath (VertexDescriptor& start, VertexDescriptor& goal) const{

    vector<VertexDescriptor> p(num_vertices(city_graph_));
    vector<Cost> d(num_vertices(city_graph_));

    LocationMap locations = get(&VertexInfo::location, city_graph_);

    
    try {
    // call astar named parameter interface
    astar_search_tree (city_graph_, start, distance_heuristic<CityGraphList, Cost, LocationMap> (locations, goal),
      weight_map(get(&EdgeInfo::cost, city_graph_)).
      vertex_index_map(get(&VertexInfo::id, city_graph_)).
      predecessor_map(make_iterator_property_map(p.begin(), get(&VertexInfo::id, city_graph_))).
      distance_map(make_iterator_property_map(d.begin(), get(&VertexInfo::id, city_graph_))).
      visitor(astar_goal_visitor<VertexDescriptor>(goal)));
    } 
  catch(found_goal fg) { // found a path to the goal
    list<VertexDescriptor> shortest_path;
    for(VertexDescriptor v = goal;; v = p[v]) {
      shortest_path.push_front(v);
      if(p[v] == v)
        break;
    }
    return shortest_path;
  }
  

  return std::list<CityGraph::VertexDescriptor>();
}
