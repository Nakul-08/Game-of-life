# CMakeList.txt : CMake project for GameOfLife
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Werror -Wall -Wextra -Wshadow -Wwrite-strings -Wno-parentheses -Weffc++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Give the project a name
project(GameOfLife)

find_package(OpenMP)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(SOURCES 
    src/Main.cpp
        src/GameOfLife.cpp
    src/GameOfLife.h
    src/WorldRenderer.cpp
    src/WorldRenderer.h
    src/Cell.h
)

add_executable(GameOfLife ${SOURCES})

target_link_libraries(GameOfLife sfml-graphics OpenMP::OpenMP_CXX)
