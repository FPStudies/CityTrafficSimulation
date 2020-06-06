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

#include "../../include/main/graph/Graph.h"

using namespace std;

int main(int argc, char** argv, char** envp) {

	//graph test <begin>
	CityGraph::Graph graph;
	CityGraph::VertexInfo vertex0 = {0, "a", 1, 1}, vertex1 = {1, "b", 2, 1}, vertex2 = {2, "c", 1, 2}, vertex3 = {3, "d", 2, 2};
	CityGraph::VertexDescriptor verd0, verd1, verd2, verd3;
	verd0 = graph.addVertex(vertex0);
	verd1 = graph.addVertex(vertex1);
	verd2 = graph.addVertex(vertex2);
	verd3 = graph.addVertex(vertex3);
	graph.addEdge(std::make_pair(0, 1), std::make_pair(2,2));
	graph.addEdge(std::make_pair(0, 2), std::make_pair(1,1));
	graph.addEdge(std::make_pair(3, 1), std::make_pair(2,2));
	graph.addEdge(std::make_pair(3, 2), std::make_pair(1,1));
	auto list = graph.findShortestPath(verd0, verd3);
	for (auto i = list.begin(); i!= list.end(); ++i) {
		cout<<graph.getVertex(*i).id<<" ";
	}
	cout<<"\n";
	//graph test <end>

	cout << "Hello" << endl;

	ProgramSetup setup(400, 300, "test");

	setup.render();

	/*for (int i = 0; envp[i] != NULL; ++i) {
		cout << envp[i] << "\n";
	}*/
	
	//sf::RenderWindow window(sf::VideoMode(640, 480, 32), "SFML Demo");
	/*std::shared_ptr<sf::RenderWindow> window_ptr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480, 32), "SFML Demo");

	ScreenManager screenManager;
	std::shared_ptr<StartScreen> startScreen = std::make_shared<StartScreen>();
	screenManager.addScreen(startScreen, "startScreen");

	screenManager.mainLoop(window_ptr, *startScreen);*/

	return 0;
}
