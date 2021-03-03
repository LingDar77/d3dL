@echo off
cd .\resource
windres resource.rc resource.o
cd ..
cd .\build
cmake -G "MinGW Makefiles" ..
make -j 8

