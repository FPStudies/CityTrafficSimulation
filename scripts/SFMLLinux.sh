#
#      Author: Przybysz Filip
#

wget -O SFML-2.5.1-linux-gcc-64-bit.tar.gz https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz
mkdir -p ../libraries
mv SFML-2.5.1-linux-gcc-64-bit.tar.gz ../libraries/SFML-2.5.1-linux-gcc-64-bit.tar.gz
cd ../libraries
tar zxf SFML-2.5.1-linux-gcc-64-bit.tar.gz
rm SFML-2.5.1-linux-gcc-64-bit.tar.gz
