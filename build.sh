rm -rf build
mkdir build

CCARGS="-O2 -Winit-self -Wmain -pedantic -Wall -m64 -std=c++11 -Iaux"
DEST="build/CoreBSP build/main.o build/w_init.o build/Quake3Bsp.o build/glad.o"
LINKARGS="-s -lglfw -lX11 -lXrandr -lXinerama -ldl -lpthread -lGL"

g++ $CCARGS -c src/main.cpp      -o build/main.o
g++ $CCARGS -c src/Quake3Bsp.cpp -o build/Quake3Bsp.o
g++ $CCARGS -c src/w_init.cpp    -o build/w_init.o
g++ $CCARGS -c aux/glad.c        -o build/glad.o

g++ -o $DEST $LINKARGS
rm -rf build/main.o build/w_init.o build/Quake3Bsp.o build/glad.o
./build/CoreBSP maps/Level.bsp
