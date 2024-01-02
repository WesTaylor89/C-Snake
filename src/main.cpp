#define SDL_MAIN_HANDLED

#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scoresheet.h"
#include "menu.h"
#include <iostream>
#include <thread>
#include <memory>

int main() {
    constexpr std::size_t kFramesPerSecond{60}; // start was 60
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    // Create necessary objects
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    std::unique_ptr<Controller> controller = std::make_unique<Controller>();
    Game game(kGridWidth, kGridHeight);
    Scoresheet scoreSheet;
    Menu menu;

    // Create thread variables and active bool checks
    std::thread playerThread;
    std::thread aiThread;
    bool playerThreadActive = false;
    bool aiThreadActive = false;

    // Launch player name input screen and get player name input
    // (should refactor to a single function call)
    std::string playerName;
    bool nameEntered = false;

    SDL_StartTextInput();
    while (!nameEntered) {
        renderer->RenderNameInput(playerName);

        controller->UpdateNameInput(playerName, nameEntered);
    }
    SDL_StopTextInput();
    scoreSheet.setPlayerName(playerName);

    // main menu loop
    bool quit = false;
    while (!quit) {


        // Render Menu and update as player makes selections
        renderer->RenderMenu(menu.GetOptions(), menu.GetSelectedOption());
        controller->UpdateMenu(*renderer, menu);



        switch (menu.GetSelectedOption()) {
            case 0: // Single Player

                game.SetWithAIFalse();
                // Assign thread
                playerThread = std::thread([&game, &controller]() {
                    while (!game.GetGameOver()) {
                        game.UpdatePlayer(*controller);
                        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Adjust timing as needed
                    }
                });
                playerThreadActive = true;

                // Run game
                game.Run(*controller, *renderer, kMsPerFrame);

                // Add _score to scoreboard
                scoreSheet.insertOrdered(scoreSheet.createPair(
                        scoreSheet.getPlayerName(),
                        game.GetScore()));
                std::cout << "Game has terminated successfully!\n";
                std::cout << "Score: " << game.GetScore() << "\n";
                std::cout << "Size: " << game.GetSize() << "\n";
                break;
            case 1: // vs AI

                game.SetWithAITrue();

                // Assign threads
                playerThread = std::thread([&game, &controller]() {
                    while (!game.GetGameOver()) {
                        game.UpdatePlayer(*controller);
                        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Adjust timing as needed
                    }
                });

                aiThread = std::thread([&game]() {
                    while (!game.GetGameOver()) {
                        game.UpdateAI();
                        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Adjust timing as needed
                    }
                });
                playerThreadActive = true;
                aiThreadActive = true;

                // Run game
                game.Run(*controller, *renderer, kMsPerFrame);

                // Add _score to scoreboard
                scoreSheet.insertOrdered(scoreSheet.createPair(
                        scoreSheet.getPlayerName(),
                        game.GetScore()));
                std::cout << "Game has terminated successfully!\n";
                std::cout << "Score: " << game.GetScore() << "\n";
                std::cout << "Size: " << game.GetSize() << "\n";
                break;
            case 2: // Score Board
                // ... Scoreboard logic ...
                std::cout << "Score Board menu" << std::endl;
                scoreSheet.displayScores();
                break;

            case 3: // Quit
                quit = true;
                break;
        }

        // Join threads after exiting the menu loop
        if (playerThreadActive && playerThread.joinable()) {
            playerThread.join();
            playerThreadActive = false;
        }
        if (aiThreadActive && aiThread.joinable()) {
            aiThread.join();
            aiThreadActive = false;
        }

        // Reset game state
        game.Reset();

    }

    // exit
    return 0;
}