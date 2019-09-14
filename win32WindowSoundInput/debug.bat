@echo off

mkdir data
pushd data
devenv ..\build\win32_project.exe
popd
