//
// Created by Wesley on 06/12/2023.
//

#ifndef SDL2TEST_AI_SNAKE_H
#define SDL2TEST_AI_SNAKE_H


#include "snake.h"
#include "sdl_utility.h"
#include <vector>
#include <unordered_map>
#include <deque>

class ai_snake : public Snake {
public:
    ai_snake(int grid_width, int grid_height) : Snake(grid_width, grid_height) {}

    void UpdateAI(const SDL_Point &food, const Snake &playerSnake);

private:
    int ManhattanDistance(const SDL_Point &a, const SDL_Point &b, int grid_width, int grid_height);

    std::vector<SDL_Point> CalculatePath(const SDL_Point &start, const SDL_Point &goal, const Snake &playerSnake);

    std::vector<SDL_Point> ConstructPath(const std::unordered_map<SDL_Point, SDL_Point, SDLPointHash, SDLPointEqual> &came_from, SDL_Point current);

    float speed{0.1f}; // default was 0.01f

    std::vector<SDL_Point> path;

    std::deque<SDL_Point> positionsHistory;

};

#endif //SDL2TEST_AI_SNAKE_H
