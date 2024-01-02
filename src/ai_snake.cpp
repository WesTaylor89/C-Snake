//
// Created by Wesley on 06/12/2023.
//

#include "ai_snake.h"
#include "snake.h"
#include "sdl_utility.h"
#include <queue>

// Best solution so far. AI Snake occasionally freezes but doesn't oscillate.
SDL_Point ai_snake::NextHeadPosition(Direction dir) const {
    int new_x = static_cast<int>(head_x);
    int new_y = static_cast<int>(head_y);

    switch (dir) {
        case Direction::kUp:
            new_y -= 1;
            break;
        case Direction::kDown:
            new_y += 1;
            break;
        case Direction::kLeft:
            new_x -= 1;
            break;
        case Direction::kRight:
            new_x += 1;
            break;
    }

    // Handle wrapping of coordinates
    new_x = (new_x + getGridWidth()) % getGridWidth();
    new_y = (new_y + getGridHeight()) % getGridHeight();

    return {new_x, new_y};
}


Snake::Direction ai_snake::DetermineDirection(const SDL_Point& food) {
    int dx = food.x - static_cast<int>(head_x);
    int dy = food.y - static_cast<int>(head_y);

    // Prioritize the axis with the greater distance
    if (abs(dx) > abs(dy)) {
        return (dx > 0) ? Direction::kRight : Direction::kLeft;
    } else {
        return (dy > 0) ? Direction::kDown : Direction::kUp;
    }
}

bool ai_snake::IsSafeDirection(Direction dir, const Snake& playerSnake) {
    SDL_Point futureHeadPos = NextHeadPosition(dir);
    // Check if the next position is part of the snake's body or the player's body
    if (SnakeCell(futureHeadPos.x, futureHeadPos.y) || playerSnake.SnakeCell(futureHeadPos.x, futureHeadPos.y)) {
        return false;
    }
    // Put additional checks here if needed
    return true;
}

Snake::Direction ai_snake::FindAlternativeDirection(const Snake& playerSnake) {
    std::vector<Direction> directions = {Direction::kUp, Direction::kDown, Direction::kLeft, Direction::kRight};
    Direction lastResort = direction; // Initialize with the current direction

    for (auto dir : directions) {
        if (dir != direction && IsSafeDirection(dir, playerSnake)) {
            return dir;
        } else if (dir != direction) {
            // Keep track of the last resort direction
            lastResort = dir;
        }
    }

    // If no safe direction is found, return the last resort direction
    return lastResort;
}


void ai_snake::UpdateAI(const SDL_Point& food, const Snake& playerSnake) {
    // Calculate the next step direction towards the food
    Direction nextStepDirection = DetermineDirection(food);

    // Check if the next step is safe
    if (IsSafeDirection(nextStepDirection, playerSnake)) {
        direction = nextStepDirection;
    } else {
        // If not safe, find an alternative direction
        direction = FindAlternativeDirection(playerSnake);
    }

    Update();
}

void ai_snake::Reset() {
    Snake::Reset(); // Call the base class Reset to reset inherited state

    // Reset ai_snake-specific state
    path.clear();               // Clear the path
    positionsHistory.clear();   // Clear the history of positions
}






