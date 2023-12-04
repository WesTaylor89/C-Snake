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

class Menu {
public:
    Menu();
    ~Menu();

    // Update menu based on user input
    void Update(Renderer &screenRender);

    // Getters
    int GetSelectedOption() const;
    const std::vector<std::string>& GetOptions() const;

    // Setters
    void SetSelectedOption(int option);

private:
    // Vector of Strings to hold selectable menu options
    std::vector<std::string> options;
    // Index of selected option from options vector
    int selectedOption;
};


#endif //SDL2TEST_MENU_H
