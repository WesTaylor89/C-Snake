cmake_minimum_required(VERSION 3.7)
project(SDL2Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_DIR C:/dev/vcpkg/installed/x64-windows/share/sdl2)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(SnakeGame
        src/main.cpp
        src/game.cpp
        src/controller.cpp
        src/renderer.cpp
        src/snake.cpp
        src/ScoreSheet.h
        src/ScoreSheet.cpp)

target_link_libraries(SnakeGame PRIVATE
        C:/dev/vcpkg/installed/x64-windows/lib/manual-link/SDL2main.lib
        C:/dev/vcpkg/installed/x64-windows/lib/SDL2.lib)