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

    //communication between element manager and graphs due to problems with opereating on vertex descriptors
    template<typename Key>
    class Proxy {
    private:

        Graph graph_;

        std::map<Key, VertexDescriptor> map_;

    public:

        Proxy();

        ~Proxy();

        

    };

};

#endif
