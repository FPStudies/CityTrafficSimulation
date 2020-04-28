# ZPR_CityTrafficSimulation
Simple simulation tool for modeling city traffic.

Installation:
Program requires Python, Scons, Cmake and the g++(Liux) or CL(Windows) compiler.
(Linux:
sudo apt-get install python
sudo apt-get install scons
sudo apt-get install cmake
sudo apt-get install g++)

To compile run 'scons' in the SConstruct file directory.

Rest of the libraries will be installed by the SConstruct and provided scripts.

Start the program with the runLinux.sh script on Linux.
On Windows use runWindows.sh or open cmd and type "set PATH=%PATH%;libraries\SFML-2.5.1\bin" before starting the executable from the same cmd.

Note!
On Windows automatic library installation with scripts works only with PowerShell.
Please make sure you have PowerShell v5 or later installed and permission to run scripts is given.
(Set-ExecutionPolicy RemoteSigned)