#include "renderer.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize. SDL_ttf Error: " << TTF_GetError() << "\n";
    }

    // Load a font using SDL_ttf
    font = TTF_OpenFont("C:/Users/Wesle/CLionProjects/SDL2Test/fonts/Debrosee-ALPnL.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Failed to load font. SDL_ttf Error: " << TTF_GetError() << "\n";
        // TODO: Handle error
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  TTF_CloseFont(font);
  SDL_Quit();
  TTF_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render food
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(sdl_renderer, &block);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderMenu(const std::vector<std::string> &options, int selectedOption) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Set text color
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // Define positions for rendering menu options
    int xPos = screen_width / 4; // Adjust as needed
    int yPos = screen_height / 4; // Starting vertical position for the first menu option
    int optionHeight = 50; // Height between menu options

    for (size_t i = 0; i < options.size(); i++) {
        if (i == selectedOption) {
            // Highlight the selected option, e.g., by changing its color
            textColor = {255, 255, 0, 255}; // Yellow color for selected option
        } else {
            textColor = {255, 255, 255, 255}; // White color for non-selected options
        }

        // Create surface from text
        SDL_Surface *surface = TTF_RenderText_Solid(font, options[i].c_str(), textColor);
        if (surface == nullptr) {
            std::cerr << "Unable to create text surface. SDL_ttf Error: " << TTF_GetError() << "\n";
            continue;
        }

        // Create texture from surface
        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
        if (texture == nullptr) {
            std::cerr << "Unable to create texture from surface. SDL Error: " << SDL_GetError() << "\n";
        }

        SDL_Rect renderQuad = {xPos, yPos + (int)i * optionHeight, surface->w, surface->h};
        SDL_RenderCopy(sdl_renderer, texture, nullptr, &renderQuad);

        // Clean up surface and texture
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }



    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

