#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, bool withAI)
    : snake(grid_width, grid_height),
      aiSnake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      _withAI(withAI) {
    PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    int game_running = 1;
    SetGameOverFalse();

    while (!GetGameOver()) {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        // Input
        controller.HandleInput(game_running, snake);
        if (game_running == 0) {
            SetGameOverTrue();
            break;
        }

        // Update
        // Handled in main.cpp by threads

        // Render
        if (_withAI) {
            renderer.Render(snake, aiSnake, food);
        } else {
            renderer.Render(snake, food);
        }

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000) {
            renderer.UpdateWindowTitle(_score, frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

// Place food in a random location that is not occupied by either player snake or AI snake
void Game::PlaceFood() {
    int x, y;
    while (true) {
        x = random_w(engine);
        y = random_h(engine);

        // Check that the location is not occupied by either the player snake or the AI snake
        bool isCellOccupied = snake.SnakeCell(x, y);
        if (_withAI) {
            isCellOccupied = isCellOccupied || aiSnake.SnakeCell(x, y);
        }

        if (!isCellOccupied) {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

// Handle logic for checking if either player snake or AI snake has consumed food,
// if so grow the relevant snake.
void Game::CheckFoodConsumption(Snake &snakeEntity) {
    int new_x = static_cast<int>(snakeEntity.head_x);
    int new_y = static_cast<int>(snakeEntity.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y) {
        _score++;
        PlaceFood();
        // Grow snake and increase speed.
        snakeEntity.GrowBody();
        //snakeEntity.speed += 0.02; // disbled to debug
    }
}

// Update player snake's position
void Game::UpdatePlayer(Controller const &controller) {
    std::lock_guard<std::mutex> guard(gameMutex);
    controller.HandleInput(reinterpret_cast<int &>(_gameOver), snake); // todo: not sure this works
    if (_gameOver) {
        return;
    }
    snake.Update();  // Update the player's snake
    CheckFoodConsumption(snake);  // Check if the player's snake ate food
}

// Update AI snake's position
void Game::UpdateAI() {
    std::lock_guard<std::mutex> guard(gameMutex);
    if (_gameOver || !_withAI) { // don't run AI logic in single player mode
        return;
    }
    aiSnake.UpdateAI(food, snake); // AI logic
    aiSnake.Update(); // Update AI snake's position
    CheckFoodConsumption(aiSnake);  // Check if the AI snake ate food
}


// Getters and Setters

int Game::GetScore() const { return _score; }

int Game::GetSize() const { return snake.size; }

bool Game::GetGameOver() const {
    return _gameOver;
}

void Game::SetGameOverFalse() {
    _gameOver = false;
}

void Game::SetGameOverTrue() {
    _gameOver = true;
}

void Game::SetWithAITrue() {
    _withAI = true;
}

void Game::SetWithAIFalse() {
    _withAI = false;
}

