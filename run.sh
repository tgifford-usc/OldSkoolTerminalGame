#!/usr/bin/env bash
set -e
g++ -std=c++17 -Wall -Wextra src/*.cpp src/Console/*.cpp -Iinclude -o game
./game