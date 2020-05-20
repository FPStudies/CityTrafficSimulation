#
#      Author: Przybysz Filip
#

wget https://github.com/erincatto/box2d/archive/5ae818e95ddd09622bad4fd295311ca4706ad2b2.zip -O master.zip
New-Item -ItemType Directory -force -path ..\libraries
move-item -path master.zip -destination ..\libraries\master.zip
cd ..\libraries
Expand-Archive -Path master.zip -DestinationPath .
Remove-Item master.zip
Rename-Item box2d-5ae818e95ddd09622bad4fd295311ca4706ad2b2 box2d-master
cd box2d-master
premake5.exe vs2019
cd Build
MSBuild.exe Box2D.vcxproj -property:Configuration=Release -property:Platform=x64
