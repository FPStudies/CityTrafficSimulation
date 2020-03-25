
#include <iostream>
#include "../graphic_library_facade/graphicLibraryFacade.h"
#include "renderLoop.h"

using namespace std;

int main(int argc, char** argv, char** envp) {

	cout << "Hello" << endl;

	RenderLoop render(400, 300, "test");

	render.render();

	/*for (int i = 0; envp[i] != NULL; ++i) {
		cout << envp[i] << "\n";
	}*/
	

	return 0;
}