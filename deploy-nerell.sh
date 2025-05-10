#!/bin/bash
current_dir=$(pwd=)
cd build/Nerell_Raspi_64-Release
make clean
make

scp robots-gui nerell.local:/home/pi

cd ${current_dir}