@echo off
cd .\build
cmake -G "MinGW Makefiles" ..
make -j 8