//
// Created by Wesley on 08/12/2023.
//

#ifndef SDL2TEST_SDL_UTILITY_H
#define SDL2TEST_SDL_UTILITY_H

#include <SDL.h>
#include <cstddef>
#include <string_view>

// Custom hash function for SDL_Point
struct SDLPointHash {
    std::size_t operator()(const SDL_Point& point) const noexcept {
        return std::hash<int>()(point.x) ^ (std::hash<int>()(point.y) << 1);
    }
};

// Custom equality function for SDL_Point
struct SDLPointEqual {
    bool operator()(const SDL_Point& a, const SDL_Point& b) const {
        return a.x == b.x && a.y == b.y;
    }
};

#endif //SDL2TEST_SDL_UTILITY_H
