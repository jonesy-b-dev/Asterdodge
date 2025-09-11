rm ./Makefile
./build/premake5 --file=./build/premake5.lua gmake

if ! bear -- make; then
    echo "Compilation failed stopping...."
    exit 1
fi

./bin/Debug/asterdodge
