#!/bin/sh

export PICO_SDK_PATH=$(pwd)/pico-sdk
cmake -Bbuild -G Ninja -DCMAKE_C_COMPILER=$(which arm-none-eabi-gcc) -DCMAKE_CXX_COMPILER=$(which arm-none-eabi-g++) .
cd build
ninja
