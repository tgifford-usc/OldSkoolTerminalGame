#!/usr/bin/env bash

pkill -f "^.*/game$" 2>/dev/null || true
sleep 1
clear

echo "======================================"
echo "  Terminal Game Programming Exercise"
echo "======================================"
echo
echo "1. Edit these files:"
echo "   src/TerminalCartridge.cpp"
echo "   include/TerminalCartridge.h"
echo
echo "2. Run the game:"
echo
echo "   Terminal → Run Task → ▶ Run Terminal Game"
echo
echo "======================================"
