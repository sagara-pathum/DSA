#!/bin/bash
cd "$(dirname "$0")"
cp ../modules/Pzl.cpp ../modules/Pzl_fixed.cpp
sed -i 's/std::random_device r = std::random_device();/std::random_device r;/' ../modules/Pzl_fixed.cpp
sed -i 's/std::uniform_int_distribution vec_moves/std::uniform_int_distribution<int> vec_moves/' ../modules/Pzl_fixed.cpp
g++ -std=c++11 -o run_test test.cpp ../modules/Pzl_fixed.cpp -lncurses
rm ../modules/Pzl_fixed.cpp
echo "Compiled! Run with: ./run_test"
