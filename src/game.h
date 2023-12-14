#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "ai_snake.h"

class Game {
 public:
    // constructor
    Game(std::size_t grid_width, std::size_t grid_height, bool withAI = false);

    // member functions
    void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

    static int GameLogicThread(void* data);

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
    SDL_Point food;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int _score{0};
    bool _gameOver = false;
    bool _withAI = false; // determine if the game is played with AI

    void PlaceFood();
    void Update();
    void CheckFoodConsumption(Snake &snake);

    std::size_t currentFrame = 0;

};

#endif