/*
 * Main.cc
 *
 *      Author: Kordowski Mateusz
 */

#include <iostream>
#include "../../include/ProgramSetup.h"

#include "../../include/main/screen/ScreenManager.h"
#include "../../include/main/screen/StartScreen.h"

using namespace std;

int main(int argc, char** argv, char** envp) {

	ProgramSetup setup(1920, 1080, "City trafic simulator");

	setup.setup();

	setup.render();

	return 0;
}
