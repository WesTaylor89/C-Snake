//
// Created by Wesley on 27/11/2023.
//

#ifndef SDL2TEST_MENU_H
#define SDL2TEST_MENU_H


#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <menu.h>
#include "renderer.h"

// The menu class holds a vector of the options rendered on the main menu.
// It also owns the _selectedOption variable with tells the renderer class what to render
class Menu {
public:
    // Constructor
    Menu();
    // Destructor
    ~Menu();

    // Getters
    int GetSelectedOption() const;
    const std::vector<std::string>& GetOptions() const;

    // Setters
    void SetSelectedOption(int option);

private:
    // Vector of Strings to hold selectable menu _options
    std::vector<std::string> _options;
    // Index of selected option from _options vector
    int _selectedOption;
};


#endif //SDL2TEST_MENU_H
