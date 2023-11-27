cmake_minimum_required(VERSION 3.7)
project(SDL2Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(SnakeGame
        src/main.cpp
        src/game.cpp
        src/controller.cpp
        src/renderer.cpp
        src/snake.cpp
        src/scoreSheet.h
        src/scoreSheet.cpp
        src/menu.h
        src/menu.cpp
)

target_include_directories(SnakeGame PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        src)

target_link_libraries(SnakeGame PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
        SDL2_ttf::SDL2_ttf)