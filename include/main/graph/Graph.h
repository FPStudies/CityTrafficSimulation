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

        VertexPropertyMap vertices_;

        WeightMap weights_;

        bool is_build_;

    public:

        Graph();

        ~Graph() = default;

        void buildGraph(long number_of_vertices, const std::vector<Edge>& edges, const std::vector<double>& weights);

        std::list<CityGraph::Vertex> findShortestPath (Vertex& start, Vertex& goal) const;

        const bool isBuild() const;

    };

}
#endif