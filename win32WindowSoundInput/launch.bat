@echo off

mkdir data
pushd data
call ..\build\win32_project.exe
popd
