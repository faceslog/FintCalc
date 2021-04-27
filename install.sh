#!/bin/bash

sudo apt install build-essential -y
sudo apt install cmake -y
sudo apt install libsdl2-dev -y

mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
./FintCalc

