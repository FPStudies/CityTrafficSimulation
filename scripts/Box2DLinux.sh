#
#      Author: Przybysz Filip
#

wget -O master.zip https://github.com/erincatto/box2d/archive/5ae818e95ddd09622bad4fd295311ca4706ad2b2.zip
mkdir -p ../libraries
mv master.zip ../libraries/master.zip
cd ../libraries
unzip -q master.zip
rm master.zip
mv box2d-5ae818e95ddd09622bad4fd295311ca4706ad2b2 box2d-master
cd box2d-master
premake5 gmake
sed -i 's/PROJECTS := Box2D HelloWorld Testbed/PROJECTS := Box2D HelloWorld/g' Build/Makefile
make -C Build
