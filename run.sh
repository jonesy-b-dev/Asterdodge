rm ./Makefile
./build/premake5 --file=./build/premake5.lua gmake
bear -- make
./bin/Debug/asterdodge
