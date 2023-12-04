#define SDL_MAIN_HANDLED

#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scoreSheet.h"
#include "menu.h"
#include <iostream>

int main() {
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kGridWidth, kGridHeight);

    scoreSheet scoreSheet;
    //scoreSheet.setPlayerName();

    Menu menu;

    std::string playerName;
    bool nameEntered = false;

    SDL_StartTextInput();
    while (!nameEntered) {
        renderer.RenderNameInputForm(playerName);

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
    SDL_StopTextInput(); // Stop text input


    bool quit = false;
    while (!quit) {

        renderer.RenderMenu(menu.GetOptions(), menu.GetSelectedOption());
        controller.Update(renderer, menu);

        switch (menu.GetSelectedOption()) {
            case 0: // New Game
                // Run game
                game.Run(controller, renderer, kMsPerFrame);

                // Add score to scoreboard
                scoreSheet.insertOrdered(scoreSheet.createPair(scoreSheet.getPlayerName(),
                                                                                                           game.GetScore()));
                std::cout << "Game has terminated successfully!\n";
                std::cout << "Score: " << game.GetScore() << "\n";
                std::cout << "Size: " << game.GetSize() << "\n";
                break;
            case 1: // Score Board
                // ... Scoreboard logic ...
                std::cout << "Score Board menu" << std::endl;
                scoreSheet.displayScores();
                break;
            case 2: // Quit
                quit = true;
                break;
        }
    }
}