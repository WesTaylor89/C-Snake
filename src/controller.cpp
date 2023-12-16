#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const {
    // Only change direction if not opposite or if the snake size is 1
    if (snake.direction != opposite || snake.size == 1) {
        snake.direction = input;
    }
}

// Handle user input for game
int Controller::HandleInput(int &game_running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
        return game_running = 0;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
      }
    }
  }
  return 1;
}

// Handle user input for menu and update currently highlighted option
// (repeated renders required for highlighting slows performance, how to fix?)
void Controller::UpdateMenu(Renderer &screenRender, Menu &menu) {
    SDL_Event e;
    bool optionSelected = false;
    int selectedOption = 0;
    int optionsSize = menu.GetOptions().size();

    while (!optionSelected) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                selectedOption = optionsSize - 1; // Set to Quit
                menu.SetSelectedOption(selectedOption);
                optionSelected = true;
            } else if (e.type == SDL_KEYDOWN) { // listen for keydown events
                switch (e.key.keysym.sym) { // check keycode
                    case SDLK_UP:
                        selectedOption = (selectedOption + optionsSize - 1) % optionsSize;
                        menu.SetSelectedOption(selectedOption);
                        // rerender page to update selected option highlight
                        screenRender.RenderMenu(menu.GetOptions(), menu.GetSelectedOption());
                        break;
                    case SDLK_DOWN:
                        selectedOption = (selectedOption + 1) % optionsSize;
                        menu.SetSelectedOption(selectedOption);
                        screenRender.RenderMenu(menu.GetOptions(), menu.GetSelectedOption());
                        break;
                    case SDLK_RETURN:
                        optionSelected = true;
                        break;
                }
            }
        }
    }
}

// Handle user input for name input menu
void Controller::UpdateNameInput(std::string &playerName, bool &nameEntered) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            nameEntered = true; // or handle the quit event as needed
        } else if (e.type == SDL_TEXTINPUT) {
            playerName += e.text.text; // Append the character
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_BACKSPACE && !playerName.empty()) {
                playerName.pop_back(); // Remove last character
            } else if (e.key.keysym.sym == SDLK_RETURN) {
                nameEntered = true; // Finish text input
            }
        }
    }
}