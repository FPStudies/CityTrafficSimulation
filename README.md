# CityTrafficSimulation
Simple simulation tool for modeling city traffic.

Authors: Kordowski Mateusz, Przybysz Filip


Installation:
Program requires Python, Scons, premake5, and the g++(Linux) or CL(Windows) compiler.
(Linux:
sudo apt-get install python
sudo apt-get install scons
sudo apt-get install cmake
sudo apt-get install g++)

To compile the program run 'scons' in the SConstruct file directory.

Missing required libraries (Boost, SFML, Box2D) will be installed by the SConstruct and provided scripts.


Start the program with the runLinux.sh script on Linux.
On Windows use runWindows.sh or open cmd and type "set PATH=%PATH%;libraries\SFML-2.5.1\bin" before starting the executable from the same cmd.


Tests:
To compile the tests run 'scons --build tests' in the SConstruct file directory.
Start all tests with the runTestsLinux.sh or runTestsWindows.sh.


Note!
On Windows automatic library installation with scripts works only with PowerShell.
Please make sure you have PowerShell v5 or later installed and permission to run scripts is given.
(Set-ExecutionPolicy RemoteSigned)
Automatic Box2D library installation on Windows also requires MSBuild and might require changing platform toolset if you're not using VS2017 v141 by default.
