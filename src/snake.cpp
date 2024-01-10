#include "snake.h"
#include <cmath>

void Snake::Update() {
    SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)};  // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)};  // Capture the head's cell after updating.

    // Update all the body vector items if the snake head has moved to a new
    // cell.
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
        UpdateBody(current_cell, prev_cell);
    }
    //std::cout << "AI Snake Position: (" << head_x << ", " << head_y << ")" << std::endl; // debug output
}

void Snake::UpdateHead() {
    //std::cout << "Before Update - Head Position: (" << head_x << ", " << head_y << ")" << std::endl; // debug output
    switch (direction) {
        case Direction::kUp:
            head_y -= speed;
            break;

        case Direction::kDown:
            head_y += speed;
            break;

        case Direction::kLeft:
            head_x -= speed;
            break;

        case Direction::kRight:
            head_x += speed;
            break;
    }
    //std::cout << "After Update - Head Position: (" << head_x << ", " << head_y << ")" << std::endl; // debug output


    // Wrap the Snake around to the beginning if going off of the screen.
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

// Predict the future head position based on the current head position
SDL_Point Snake::NextHeadPosition(Direction dir) const {
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

    // Handle wrapping of coordinates if your game allows it
    new_x = fmod(new_x + grid_width, grid_width);
    new_y = fmod(new_y + grid_height, grid_height);

    return {new_x, new_y};
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
    // Add previous head location to vector
    body.push_back(prev_head_cell);

    if (!growing) {
        // Remove the tail from the vector.
        body.erase(body.begin());
    } else {
        growing = false;
        size++;
    }

    // Check if the snake has died.
    for (auto const &item : body) {
        if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
            alive = false;
        }
    }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) const {
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
        return true;
    }
    for (auto const &item : body) {
        if (x == item.x && y == item.y) {
            return true;
        }
    }
    return false;
}

// ResetState Snake State
void Snake::Reset() {
    // ResetState the snake's size to 1
    size = 1;

    // ResetState the snake's position to the center of the grid
    head_x = grid_width / 2;
    head_y = grid_height / 2;

    // Clear the body vector, as the snake will be back to its initial size
    body.clear();

    // ResetState the snake's direction
    direction = Direction::kUp;

    // ResetState other relevant attributes
    alive = true;
    growing = false;
    speed = 0.1f; // ResetState to default speed or any initial speed
}

int Snake::getGridWidth() const {
    return grid_width;
}
void Snake::setGridWidth(int width) {
    grid_width = width;
}

int Snake::getGridHeight() const {
    return grid_height;
}

void Snake::setGridHeight(int height) {
    grid_height = height;
}

bool Snake::ShouldIncreaseScore() const {
    return isPlayerControlled;
}

void Snake::SetAsPlayerControlled(bool PlayerControlled) {
    this->isPlayerControlled = PlayerControlled;
}



