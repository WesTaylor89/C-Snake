//
// Created by Wesley on 27/11/2023.
//

#include "menu.h"
#include "renderer.h"
#include <SDL2/SDL.h>

Menu::Menu() : selectedOption(0) {
    options = {"New Game", "Score Board", "Quit"};
}

Menu::~Menu() {
    // Cleanup if needed
}

int Menu::GetSelectedOption() const {
    return selectedOption;
}

const std::vector<std::string>& Menu::GetOptions() const {
    return options;
}

void Menu::SetSelectedOption(int option) {
    selectedOption = option;
}
