#!/bin/bash
set -e
rm -rf build
rm -rf server/generated
rm -rf generated
conan install . --build=missing -s build_type=Debug
cmake --preset conan-debug
cmake --build --preset conan-debug