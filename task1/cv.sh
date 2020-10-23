#!/bin/bash

gs opencv`  -o  `basename $1.cpp .cpp`  $1.cpp  `pkg-config --libs opencv` -std=c++14
