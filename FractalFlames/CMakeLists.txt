cmake_minimum_required(VERSION 3.5)
project(FractalFlames.exe)

# Buffer2D
include_directories("../Buffer2D")

# PPM
include_directories("../ppm")
set(PPM_SOURCES "../ppm/ppm.cpp")

# project files
include_directories("src")
set(PROJECT_SOURCES "src/main.cpp"
		"src/FlameFunctor.cpp"
		"src/Color.cpp")

# main target
add_executable(FractalFlames.exe ${PROJECT_SOURCES} ${PPM_SOURCES})
target_link_libraries(FractalFlames.exe)
