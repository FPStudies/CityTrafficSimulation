wget https://github.com/erincatto/box2d/archive/master.zip -OutFile master.zip
move-item -path master.zip -destination ..\libraries\master.zip
cd ..\libraries
Expand-Archive -Path master.zip -DestinationPath .
Remove-Item master.zip
cd box2d-master
((Get-Content -path CMakeLists.txt -Raw) -replace 'BOX2D_BUILD_TESTBED "Build the Box2D testbed" ON','BOX2D_BUILD_TESTBED "Build the Box2D testbed" OFF') | Set-Content -Path CMakeLists.txt
./build.bat