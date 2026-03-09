#!/usr/bin/env bash
set -e
g++ -std=c++17 main.cpp Terminal.cpp Cartridge.cpp TerminalCartridge.cpp -o game
./game