#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "ai_snake.h"

// The Game class handles the logic for running the main game loop.
class Game {
 public:
    // constructor
    Game(std::size_t grid_width, std::size_t grid_height, bool withAI = false);

    // member functions
    void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
    void UpdatePlayer(Controller const &controller);
    void UpdateAI();
    void ResetState();

    // Getters
    int GetScore() const;
    int GetSize() const;
    bool GetGameOver() const;

    // Setters
    void SetGameOverTrue();
    void SetGameOverFalse();
    void SetWithAITrue();
    void SetWithAIFalse();



 private:
    Snake snake;
    ai_snake aiSnake;
    SDL_Point food{};
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
    std::mutex gameMutex;
    int _score{0};
    bool _gameOver = false;
    bool _withAI = false;

    void PlaceFood();
    void CheckFoodConsumption(Snake &snake);
};

#endif