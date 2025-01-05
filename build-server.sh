#!/bin/bash

rm -rf build
rm -rf server/generated
rm -rf generated
conan install . --build=missing
cmake --preset conan-release
cmake --build --preset conan-release


./build/Release/PokerMain