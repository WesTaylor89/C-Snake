# CPPND: Capstone Snake Game by Wes Taylor

This is a my submission for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post.

## Additional Features
* Players can enter their names when starting the app.
* Upon entering their name players are brought to the main menu.
* There are two game modes. The original and a Player versus AI Snake mode.
* Scores for all modes are recorded and saved to file locally.
* Scores can be viewed in a rendered state in game via the Scoreboard option.

## Rubric points addressed
* Loops, Functions, I/O
  * The project demonstrates an understanding of C++ functions and control structures
    * These are added throughout the new classes
  * The project reads data from a file and process the data, or the program writes data to a file.
    * TODO
  * The project accepts user input and processes the input
    * The Scoresheet, Render and Controller class make use of the players name.
  * The project uses data structures and immutable variables
    * Consts and Vectors are used throughout the project, example vector "scores" in scoresheet.h

* OOP
  * One or more classes are added to the project with appropriate access specifiers for class members.
    * New classes include menu, scoresheet and ai_snake
  * Classes abstract implementation details from their interfaces.
    * Classes make use of getters and setters to abstract implementation details away. 
    * All classes and functions are commented to describe their function and effects.
  * Classes follow an appropriate inheritance hierarchy with virtual and override functions.
    * Ai_snake inherits from the snake class and overrides functions from the snake class.

* Memory Management
  * The project makes use of references in function declarations.
    * Pass by reference and reference variables are used throughout the project. 
    * Examples of pass by reference can be found in the Controller class.
  * The project uses smart pointers instead of raw pointers.
    * The Renderer class makes uses of smart pointers.
  * The project uses destructors appropriately.
    * Destructors are used throughout. The Rendererer class uses a custom destructor.

* Concurrency
  * The project uses multithreading.
    * The player and ai game logic updating are performed in seperate threads created in the main class.
  * A mutex or lock is used in the project.
    * The updates to player and ai logic make use of mutex's to avoid race conditions. 
    * See game.cpp lines 115 - 133

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_ttf >= 2.20.2
  * Can be found here: https://github.com/libsdl-org/SDL_ttf/releases
  * You may have to add FindSDL2TTF.cmake to your cmake folder. It can be found in the FindSDL2TTF folder
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

* Note that you may need to add SDL2d.dll and SDL2_tff.dll (installed when you install the libraries)
* to your systems path if using Windows. This link may help:
* https://www.studyplan.dev/sdl-dev/sdl-setup-windows
* If using Windows the eaisest way to install SDL2 and SLD2_tff is to use vcpkg:
* https://github.com/microsoft/vcpkg

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
