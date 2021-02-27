@echo off
cd .\build
cmake -G "MinGW Makefiles" ..
make CFLAG=-O2