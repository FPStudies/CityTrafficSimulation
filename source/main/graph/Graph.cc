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

void Graph::removeVertex(VertexDescriptor vertex) {
  clear_vertex(vertex);
  remove_vertex(vertex);
}

const VertexInfo Graph::getVertex(VertexDescriptor vertex) const {
  return city_graph_[vertex];
}

const EdgeInfo Graph::getEdge(EdgeDescriptor edge) const {
  return city_graph_[edge];
}

void Graph::setVertexName(VertexDescriptor vertex, std::string name) {
  city_graph_[vertex].name_ = name;
}

void Graph::setVertexLocation(VertexDescriptor vertex, double x, double y) {
  city_graph_[vertex].location_.x_ = x;
  city_graph_[vertex].location_.y_ = y;
}

void Graph::setEdgeCost(EdgeDescriptor edge, Cost cost) {
  city_graph_[edge].cost_ = cost;
}


std::pair<EdgeDescriptor, EdgeDescriptor> Graph::addEdge(Edge edge, Cost cost_A_B, Cost cost_B_A) {
  EdgeDescriptor edge_1, edge_2;
  bool inserted_1, inserted_2;

  boost::tie(edge_1, inserted_1) = add_edge(edge.first, edge.second, city_graph_);
  city_graph_[edge_1].cost_ = cost_A_B;
  boost::tie(edge_2, inserted_2) = add_edge(edge.second, edge.first, city_graph_);
  city_graph_[edge_2].cost_ = cost_B_A;

  return std::make_pair(edge_1, edge_2);
}

std::pair<EdgeDescriptor, EdgeDescriptor> Graph::addEdge(Edge edge, Cost cost) {
  return addEdge(edge, cost, cost);
}

void Graph::removeEdge(Edge edge) {
  remove_edge(edge.first, edge.second);
  remove_edge(edge.second, edge.first);
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
        city_graph_[edge].cost_ = weights[i];
    }
}


std::list<CityGraph::VertexDescriptor> Graph::findShortestPath (VertexDescriptor& start, VertexDescriptor& goal) const{

    vector<VertexDescriptor> predecessor(num_vertices(city_graph_));
    vector<Cost> distance(num_vertices(city_graph_));

    LocationMap locations = get(&VertexInfo::location_, city_graph_);
    list<VertexDescriptor> shortest_path;
    
    try {
    // call astar named parameter interface
    astar_search_tree (city_graph_, start, distance_heuristic<CityGraphList, Cost, LocationMap> (locations, goal),
      weight_map(get(&EdgeInfo::cost_, city_graph_)).
      vertex_index_map(get(&VertexInfo::id_, city_graph_)).
      predecessor_map(make_iterator_property_map(predecessor.begin(), get(&VertexInfo::id_, city_graph_))).
      distance_map(make_iterator_property_map(distance.begin(), get(&VertexInfo::id_, city_graph_))).
      visitor(astar_goal_visitor<VertexDescriptor>(goal)));
    } 
  catch(found_goal fg) { // found a path to the goal
    for(VertexDescriptor v = goal;; v = predecessor[v]) {
      shortest_path.push_front(v);
      if(predecessor[v] == v)
        break;
    }
    return shortest_path;
  }
  
  //TODO: throw error
  //no path found
  return shortest_path;
}
