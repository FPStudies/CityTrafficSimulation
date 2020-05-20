#
#      Author: Przybysz Filip
#

wget -O boost_1_72_0.tar.bz2 https://sourceforge.net/projects/boost/files/boost/1.72.0/boost_1_72_0.tar.bz2/download
mkdir -p ../libraries
mv boost_1_72_0.tar.bz2 ../libraries/boost_1_72_0.tar.bz2
cd ../libraries
tar xjf boost_1_72_0.tar.bz2
rm boost_1_72_0.tar.bz2

