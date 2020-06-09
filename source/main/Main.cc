/*
 * Main.cc
 *
 *      Author: Kordowski Mateusz
 */

#include <iostream>
#include "../../include/GraphicLibraryFacade.h"
#include "../../include/ProgramSetup.h"

#include "../../include/main/screen/ScreenManager.h"
#include "../../include/main/screen/StartScreen.h"

#include "../../include/main/graph/Proxy.hpp"

using namespace std;

int main(int argc, char** argv, char** envp) {

	//graph test <begin>
	CityGraph::Proxy<Draw::DrawID> proxy;
	CityGraph::Graph graph;
	CityGraph::VertexInfo vertex0 = {0, "a", 1, 1}, vertex1 = {1, "b", 2, 1}, vertex2 = {2, "c", 1, 2}, vertex3 = {3, "d", 2, 2};
	CityGraph::VertexDescriptor verd0, verd1, verd2, verd3;
	verd0 = graph.addVertex(vertex0);
	verd1 = graph.addVertex(vertex1);
	verd2 = graph.addVertex(vertex2);
	verd3 = graph.addVertex(vertex3);
	graph.addEdge(std::make_pair(verd0, verd1), 2, 2);
	graph.addEdge(std::make_pair(verd0, verd2), 1, 1);
	graph.addEdge(std::make_pair(verd3, verd1), 2, 2);
	graph.addEdge(std::make_pair(verd3, verd2), 1, 1);
	auto list = graph.findShortestPath(verd0, verd3);
	for (auto i = list.begin(); i!= list.end(); ++i) {
		cout<<graph.getVertex(*i).id_<<" ";
	}
	cout<<"\n";
	//graph test <end>

	cout << "Hello" << endl;
	ProgramSetup setup(1920, 1080, "City trafic simulator");

	setup.setup();

	setup.render();

	return 0;
}
