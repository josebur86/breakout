#!/bin/bash

ctags -R .

mkdir -p build

DisabledWarnings=-Wno-writable-strings

g++ -std=c++11 -g code/generate_gl_init.cpp $DisabledWarnings -o build/generate_gl_init
./build/generate_gl_init

CompilerOptions=-I/usr/local/include/SDL2
LinkerOptions="-L/usr/local/lib -lSDL2 -framework OpenGL"

g++ -std=c++11 -g code/main.cpp $LinkerOptions $DisabledWarnings $CompilerOptions  -o build/breakout
