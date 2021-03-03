@echo off
cd .\build
cmake -G "MinGW Makefiles" ..
make -j 8
cd ..
cd .\resource
windres resource.rc resource.o