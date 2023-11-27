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

void Menu::Update(Renderer &screenRender) {
    SDL_Event e;
    bool optionSelected = false;

    while (!optionSelected) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                selectedOption = options.size() - 1; // Set to Quit
                optionSelected = true;
            } else if (e.type == SDL_KEYDOWN) { // listen for keydown events
                switch (e.key.keysym.sym) { // check keycode
                    case SDLK_UP:
                        selectedOption = (selectedOption + options.size() - 1) % options.size();
                        // rerender page to update selected option highlight
                        screenRender.RenderMenu(GetOptions(), GetSelectedOption());
                        break;
                    case SDLK_DOWN:
                        selectedOption = (selectedOption + 1) % options.size();
                        screenRender.RenderMenu(GetOptions(), GetSelectedOption());
                        break;
                    case SDLK_RETURN:
                        optionSelected = true;
                        break;
                }
            }
        }
    }
}

int Menu::GetSelectedOption() const {
    return selectedOption;
}

const std::vector<std::string>& Menu::GetOptions() const {
    return options;
}
