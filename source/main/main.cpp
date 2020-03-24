
#include <iostream>
#include "../graphic_library_facade/graphicLibraryFacade.h"

using namespace std;

int main(int argc, char** argv, char** envp) {

	cout << "Hello" << endl;

	GraphicFacade tmp;
	tmp.test();

	/*for (int i = 0; envp[i] != NULL; ++i) {
		cout << envp[i] << "\n";
	}*/
	

	return 0;
}