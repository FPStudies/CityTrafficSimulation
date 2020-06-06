/*
 * Graph.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_GRAPH_H
#define TRAFFIC_SIM_GRAPH_H

#include "GraphUtility.hpp"

using namespace std;
using namespace boost;

namespace CityGraph {

    class Graph {

    private:

        CityGraphList city_graph_;

    public:

        Graph();

        ~Graph() = default;

        VertexDescriptor addVertex(VertexInfo vertex_info);

        //adds edges in both directions
        std::pair<EdgeDescriptor, EdgeDescriptor> addEdge(Edge edge, std::pair<Cost, Cost> costs);

        void buildGraph(const std::vector<VertexInfo>& vertex_info, const std::vector<Edge>& edges, const std::vector<Cost>& weights);

        std::list<CityGraph::VertexDescriptor> findShortestPath (VertexDescriptor& start, VertexDescriptor& goal) const;

    };

}

#endif
