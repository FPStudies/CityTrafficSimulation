wget -O master.zip https://github.com/erincatto/box2d/archive/master.zip
mv master.zip ../libraries/master.zip
cd ../libraries
unzip -q master.zip
rm master.zip
cd box2d-master
sed -i 's/option(BOX2D_BUILD_TESTBED "Build the Box2D testbed" ON)/option(BOX2D_BUILD_TESTBED "Build the Box2D testbed" OFF)/g' CMakeLists.txt
./build.sh
