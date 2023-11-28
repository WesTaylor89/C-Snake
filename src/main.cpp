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

    bool quit = false;
    while (!quit) {

        renderer.RenderMenu(menu.GetOptions(), menu.GetSelectedOption());
        menu.Update(renderer);

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