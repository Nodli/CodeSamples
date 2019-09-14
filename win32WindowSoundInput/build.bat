@echo off

set CompilerFlags= -Zi -FC /D "_UNICODE" /D "UNICODE"
set LinkerFlags= user32.lib gdi32.lib opengl32.lib

mkdir build
pushd build
cl %CompilerFlags% ..\code\win32_project.cpp %LinkerFlags%
popd

