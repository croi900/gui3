@echo off
premake5 gmake2 && cd build && mingw32-make && cd .. && cd .\bin\Debug && gui3.exe && cd .. && cd ..
