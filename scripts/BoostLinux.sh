wget -O boost_1_72_0.tar.bz2 https://sourceforge.net/projects/boost/files/boost/1.72.0/boost_1_72_0.tar.bz2/download
mv boost_1_72_0.tar.bz2 ../libraries/boost_1_72_0.tar.bz2
cd ../libraries
tar xjf boost_1_72_0.tar.bz2
rm boost_1_72_0.tar.bz2
export LD_LIBRARY_PATH = SFML=2.5.1/lib
