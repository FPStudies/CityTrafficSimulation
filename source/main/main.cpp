
#include <iostream>
#include "../graphic_library_facade/graphicLibraryFacade.h"
#include "renderLoop.h"

#include "screen/screenManager.h"
#include "screen/startScreen.h"

using namespace std;

int main(int argc, char** argv, char** envp) {

	cout << "Hello" << endl;

	/*RenderLoop render(400, 300, "test");

	render.render();*/

	/*for (int i = 0; envp[i] != NULL; ++i) {
		cout << envp[i] << "\n";
	}*/
	
	//sf::RenderWindow window(sf::VideoMode(640, 480, 32), "SFML Demo");
	std::shared_ptr<sf::RenderWindow> window_ptr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480, 32), "SFML Demo");

	ScreenManager screenManager;
	std::shared_ptr<StartScreen> startScreen = std::make_shared<StartScreen>();
	screenManager.addScreen(startScreen, "startScreen");

	screenManager.mainLoop(window_ptr, *startScreen);

	return 0;
}