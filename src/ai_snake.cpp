//
// Created by Wesley on 06/12/2023.
//

#include "ai_snake.h"
#include "sdl_utility.h"
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cmath>

// Define a structure for nodes in the A* algorithm
struct Node {
    SDL_Point position;
    double g_cost; // Cost from start to node
    double h_cost; // Heuristic cost from node to goal
    double f_cost() const { return g_cost + h_cost; } // Total cost
    SDL_Point came_from; // Previous node in the path
    bool operator>(const Node& other) const { return f_cost() > other.f_cost(); }
};


// Manhattan distance between two SDL_Points
int ai_snake::ManhattanDistance(const SDL_Point &a, const SDL_Point &b, int grid_width, int grid_height) {
    int dx = std::abs(a.x - b.x);
    int dy = std::abs(a.y - b.y);

    // Consider wrapping for shortest distance
    dx = std::min(dx, grid_width - dx);
    dy = std::min(dy, grid_height - dy);

    return dx + dy;
}

// Reconstruct the path from the start node to the goal node after the A* algorithm
// has been completed. It traces the path backwards from the goal to the start by
// following the came_from map, which records where each node was reached from.
std::vector<SDL_Point>ai_snake::ConstructPath(const std::unordered_map<SDL_Point, SDL_Point, SDLPointHash, SDLPointEqual> &came_from, SDL_Point current) {
    std::vector<SDL_Point> path;
    auto current_point = current;
    while (came_from.find(current_point) != came_from.end()) {
        path.push_back(current_point);
        current_point = came_from.at(current_point);
    }
    std::reverse(path.begin(), path.end());
    return path;
}


std::vector<SDL_Point> ai_snake::CalculatePath(const SDL_Point& start, const SDL_Point& goal, const Snake& playerSnake) {

    std::priority_queue<Node, std::vector<Node>, std::greater<>> open_set;
    std::unordered_map<SDL_Point, double, SDLPointHash, SDLPointEqual> g_score;
    std::unordered_map<SDL_Point, SDL_Point, SDLPointHash, SDLPointEqual> came_from;

    // Initialize g_score
    for (int x = 0; x < getGridWidth(); ++x) {
        for (int y = 0; y < getGridHeight(); ++y) {
            g_score[{x, y}] = std::numeric_limits<double>::max();
        }
    }
    g_score[start] = 0.0;

    // Add start node to the open set
    open_set.push({start, 0.0, static_cast<double>(ManhattanDistance(start, goal, getGridWidth(), getGridHeight()))});

    while (!open_set.empty()) {
        Node current = open_set.top();
        open_set.pop();

        // Goal reached
        if (current.position.x == goal.x && current.position.y == goal.y) {
            return ConstructPath(came_from, current.position);
        }

        // Define the possible moves (up, down, left, right)
        std::vector<SDL_Point> moves = {
                {current.position.x, current.position.y - 1}, // Up
                {current.position.x, current.position.y + 1}, // Down
                {current.position.x - 1, current.position.y}, // Left
                {current.position.x + 1, current.position.y}  // Right
        };

        for (const auto& move : moves) {
            // No need to check for out-of-bounds as we're wrapping coordinates
            // Check if the move is not occupied by the player snake or the AI snake
            if (playerSnake.SnakeCell(move.x, move.y) || SnakeCell(move.x, move.y)) {
                continue; // Skip cells occupied by the player snake or the AI snake
            }

            // Calculate g_score for the move
            double tentative_g_score = current.g_cost + 1; // Assume cost of 1 for each move

            // If this path to the neighbor is better, record it
            if (tentative_g_score < g_score[move]) {
                came_from[move] = current.position;
                g_score[move] = tentative_g_score;
                double h_cost = ManhattanDistance(move, goal, getGridWidth(), getGridHeight());
                open_set.push({move, tentative_g_score, h_cost});
            }
        }
    }

    return {}; // Return an empty path if no path is found
}

// working but less sophisticated

// Update AI Snake's state based on calculated path towards the food while
// avoiding the player snake
//void ai_snake::UpdateAI(const SDL_Point& food, const Snake& playerSnake) {
//    // Calculate the path to the food
//    auto path = CalculatePath({static_cast<int>(head_x), static_cast<int>(head_y)}, food, playerSnake);
//
//    std::cout << "Path size: " << path.size() << std::endl; // Debug output
//    // Check if a path exists
//    if (!path.empty()) {
//        // Get the next step in the path
//        SDL_Point next_step = path.front();
//
//        std::cout << "Next step: (" << next_step.x << ", " << next_step.y << ")" << std::endl; // Debug output
//
////        // Determine the direction to move based on the next step
////        if (next_step.x < head_x) {
////            direction = Direction::kLeft;
////            //std::cout << "left" << std::endl;
////        } else if (next_step.x > head_x) {
////            direction = Direction::kRight;
////            //std::cout << "right" << std::endl;
////        } else if (next_step.y < head_y) {
////            direction = Direction::kUp;
////            //std::cout << "up" << std::endl;
////        } else if (next_step.y > head_y) {
////            direction = Direction::kDown;
////            //std::cout << "down" << std::endl;
////        }
//
//        // Determine the direction to move based on the next step
//        if (next_step.x < round(head_x)) {
//            direction = Direction::kLeft;
//        } else if (next_step.x > round(head_x)) {
//            direction = Direction::kRight;
//        } else if (next_step.y < round(head_y)) {
//            direction = Direction::kUp;
//        } else if (next_step.y > round(head_y)) {
//            direction = Direction::kDown;
//        }
//
//
//
//        // Move the AI snake in the determined direction
//        Update();
//    }
//}


void ai_snake::UpdateAI(const SDL_Point& food, const Snake& playerSnake) {
    auto path = CalculatePath({static_cast<int>(head_x), static_cast<int>(head_y)}, food, playerSnake);

    if (!path.empty()) {
        SDL_Point next_step = path.front();

        // Calculate distance in x and y directions
        int dx = next_step.x - static_cast<int>(round(head_x));
        int dy = next_step.y - static_cast<int>(round(head_y));

        // Handle wrapping of coordinates
        if (dx > getGridWidth() / 2) {
            dx -= getGridWidth();
        } else if (dx < -getGridWidth() / 2) {
            dx += getGridWidth();
        }

        if (dy > getGridHeight() / 2) {
            dy -= getGridHeight();
        } else if (dy < -getGridHeight() / 2) {
            dy += getGridHeight();
        }

        // Determine which axis to prioritize based on the greater distance
        if (abs(dx) > abs(dy)) {
            // Prioritize horizontal movement
            if (dx != 0) {
                direction = (dx > 0) ? Direction::kRight : Direction::kLeft;
            }
        } else {
            // Prioritize vertical movement
            if (dy != 0) {
                direction = (dy > 0) ? Direction::kDown : Direction::kUp;
            }
        }

        Update();
    }
}




