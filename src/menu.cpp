//
// Created by Wesley on 27/11/2023.
//

#include "menu.h"
#include "renderer.h"
#include <SDL2/SDL.h>

Menu::Menu() : _selectedOption(0) {
    _options = {"Single Player", "Vs AI", "Score Board", "Quit"};
}

Menu::~Menu() {
    // Cleanup if needed
}

int Menu::GetSelectedOption() const {
    return _selectedOption;
}

const std::vector<std::string>& Menu::GetOptions() const {
    return _options;
}

void Menu::SetSelectedOption(int option) {
    _selectedOption = option;
}
