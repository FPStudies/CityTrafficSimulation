/*
 * Graph/Proxy.h
 *
 *      Author: Przybysz Filip
 */

#ifndef TRAFFIC_SIM_GRAPH_PROXY_H
#define TRAFFIC_SIM_GRAPH_PROXY_H

#include "Graph.h"
#include <map>

using namespace std;
using namespace boost;

namespace CityGraph {

    /**
     * @brief communication between element manager and graphs due to problems with opereating on vertex descriptors
     * 
     * @tparam Key unique vertex identifier used outside of the graph module
     */
    template<typename Key>
    class Proxy {

        using Edge = std::pair<Key, Key>;

    private:

        /**
         * @brief graph to communicate with
         * 
         */
        Graph graph_;

        /**
         * @brief map of external and internal unique vertex identifiers
         * 
         */
        std::map<Key, VertexDescriptor> map_;

        /**
         * @brief find internal unique vertex identifier knowing the key value
         * 
         * @param key external vertex identifier
         * @return VertexDescriptor internal vertex identifier
         */
        VertexDescriptor findDescriptor(Key key) {
            return map_.at(key);
        }

        /**
         * @brief find key knowing the internal unique vertex identifier
         * 
         * @param descriptor internal vertex identifier
         * @return Key external vertex identifier
         */
        Key findKey(VertexDescriptor descriptor) {
            for (auto const& element : map_) {
                if (element.second == descriptor) return element.first;
            }
            //when not found
            throw std::out_of_range("Element not found.");
            return Key();
        }

    public:

        /**
         * @brief Construct a new Graph Proxy object
         * 
         */
        Proxy() = default;

        /**
         * @brief Destroy the Graph Proxy object
         * 
         */
        ~Proxy() = default;

        /**
         * @brief add vertex to graph
         * 
         * @param key external unique vertex identifier
         * @param vertex_info vertex parameters
         */
        void addVertex (Key key, VertexInfo vertex_info) {
            VertexDescriptor vertex = graph_.addVertex(vertex_info);
            map_.insert({key, vertex});
        }

        /**
         * @brief remove vertex from graph
         * 
         * @param key external unique vertex identifier
         */
        void removeVertex(Key key) {
            graph_.removeVertex( findDescriptor(key) );
            map_.erase(key);
        }

        /**
         * @brief Set the Vertex Name parameter
         * 
         * @param key external unique vertex identifier
         * @param name new name
         */
        void setVertexName(Key key, std::string name) {
            graph_.setVertexName( findDescriptor(key), name);
        }

        /**
         * @brief Set the Vertex Location parameter
         * 
         * @param key external unique vertex identifier
         * @param x 
         * @param y 
         */
        void setVertexLocation(Key key, double x, double y) {
            graph_.setVertexLocation( findDescriptor(key), x, y);
        }

        /**
         * @brief Set the Edge Cost parameter
         * 
         * @param edge edge's start and end vertices' external identifiers
         * @param cost new weight
         */
        void setEdgeCost(Edge edge, Cost cost) {
            graph_.setEdgeCost( std::make_pair( findDescriptor(edge.first), findDescriptor(edge.second) ), cost);
        }

        /**
         * @brief connect two vertices both ways with different edge weights
         * 
         * @param edge edge's start and end vertices' external identifiers
         * @param cost_A_B cost from first vertex to second
         * @param cost_B_A cost from second vertex to first
         */
        void connect(Edge edge, Cost cost_A_B, Cost cost_B_A) {
            graph_.addEdge( std::make_pair( findDescriptor(edge.first), findDescriptor(edge.second) ), cost_A_B, cost_B_A);
        }

        /**
         * @brief  connect two vertices both ways with the same edge weights
         * 
         * @param edge edge's start and end vertices' external identifiers
         * @param cost cost of the new edges
         */
        void connect(Edge edge, Cost cost) {
            graph_.addEdge( std::make_pair( findDescriptor(edge.first), findDescriptor(edge.second) ), cost);
        }

        /**
         * @brief disconnect two vertices
         * 
         * @param edge edge's start and end vertices' external identifiers
         */
        void disconnect(Edge edge) {
            graph_.removeEdge( std::make_pair( findDescriptor(edge.first), findDescriptor(edge.second) ));
        }

        /**
         * @brief find shortest path from start to goal using A*
         * 
         * @param start start vertex
         * @param goal end vertex
         * @return std::list<Key> found path
         */
        std::list<Key> findShortestPath (Key& start, Key& goal) const {
            auto descriptor_path = graph_.findShortestPath( findDescriptor(start), findDescriptor(goal) );
            std::list<Key> key_path;

            while(descriptor_path.size()>0){
                key_path.push_back( findKey( descriptor_path.front() ));
                descriptor_path.pop_front();
            }

            return key_path;
        }

    };

};

#endif
