#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
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
}

void Controller::Update(Renderer &screenRender, Menu &menu) {
    SDL_Event e;
    bool optionSelected = false;
    int selectedOption;
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

