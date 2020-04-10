# ZPR_CityTrafficSimulation
Simple simulation tool for modeling city traffic.

Installation:
Program requires Python, Scons, Cmake and the g++ compiler.
(Linux:
sudo apt-get install python
sudo apt-get install scons
sudo apt-get install cmake
sudo apt-get install g++)

To compile run 'scons' in the SConstruct file directory.

Rest of the libraries will be installed by the SConstruct and provided scripts.

Start the program with the run.sh script on Linux.

Note!
On Windows automatic library install with scripts works only with PowerShell.
Please make sure you have PowerShell v5 or later installed and permission to run scripts is given.
(Set-ExecutionPolicy RemoteSigned)