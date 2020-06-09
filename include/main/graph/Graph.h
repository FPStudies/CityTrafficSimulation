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

    /**
     * @brief bidirectional graph for depicting possible routes in a city
     * 
     */
    class Graph {

    private:

        /**
         * @brief graph representation
         * 
         */
        CityGraphList city_graph_;

    public:

        /**
         * @brief Construct a new Graph object
         * 
         */
        Graph();

        /**
         * @brief Destroy the Graph object
         * 
         */
        ~Graph() = default;

        /**
         * @brief add vertex to graph
         * 
         * @param vertex_info vertex parameters
         * @return VertexDescriptor new vertex descriptor
         */
        VertexDescriptor addVertex(VertexInfo vertex_info);

        /**
         * @brief remove vertex from graph
         * 
         * @param vertex descriptor of the vertex to be removed
         */
        void removeVertex(VertexDescriptor vertex);

        /**
         * @brief Get the const Vertex parameters
         * 
         * @param vertex vertex descriptor
         * @return const VertexInfo vertex parameters
         */
        const VertexInfo getVertex(VertexDescriptor vertex) const;

        /**
         * @brief Get the const Edge parameters
         * 
         * @param edge edge descriptor
         * @return const EdgeInfo edge parameters
         */
        const EdgeInfo getEdge(EdgeDescriptor edge) const;

        /**
         * @brief Set the Vertex Name parameter
         * 
         * @param vertex vertex descriptor
         * @param name new name
         */
        void setVertexName(VertexDescriptor vertex, std::string name);

        /**
         * @brief Set the Vertex Location parameter
         * 
         * @param vertex vertex descriptor
         * @param x
         * @param y 
         */
        void setVertexLocation(VertexDescriptor vertex, double x, double y);

        /**
         * @brief Set the Edge Cost object
         * 
         * @param edge edge descriptor
         * @param cost new cost
         */
        void setEdgeCost(EdgeDescriptor edge, Cost cost);

        //TODO: id assertion ?

        /**
         * @brief adds edges in both directions with different costs
         * 
         * @param edge vertices to connect
         * @param cost_A_B edge cost from first vertex to second
         * @param cost_B_A edge cost form second vertex to first
         * @return std::pair<EdgeDescriptor, EdgeDescriptor> edge descriptors
         */
        std::pair<EdgeDescriptor, EdgeDescriptor> addEdge(Edge edge, Cost cost_A_B, Cost cost_B_A);

        /**
         * @brief adds edges in both directions with the same cost
         * 
         * @param edge vertices to connect
         * @param cost edge cost
         * @return std::pair<EdgeDescriptor, EdgeDescriptor> edge descriptors
         */
        std::pair<EdgeDescriptor, EdgeDescriptor> addEdge(Edge edge, Cost cost);

        /**
         * @brief removes both edges connecting the vertices
         * 
         * @param edge vertices to disconnect
         */
        void removeEdge(Edge edge);

        /**
         * @brief create graph from scratch with given information
         * 
         * @param vertex_info vertices' parameters
         * @param edges existing edges
         * @param weights edges' weights
         */
        void buildGraph(const std::vector<VertexInfo>& vertex_info, const std::vector<Edge>& edges, const std::vector<Cost>& weights);

        /**
         * @brief find shortest path in graph using A*
         * 
         * @param start starting vertex
         * @param goal end vertex
         * @return std::list<CityGraph::VertexDescriptor> found route
         */
        std::list<CityGraph::VertexDescriptor> findShortestPath (VertexDescriptor& start, VertexDescriptor& goal) const;

    };

}

#endif
