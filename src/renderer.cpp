#include "renderer.h"
#include "ai_snake.h"
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <scoresheet.h>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width,
                   const std::size_t grid_height)
        : sdl_window(nullptr, SDL_DestroyWindow),
          sdl_renderer(nullptr, SDL_DestroyRenderer),
          screen_width(screen_width),
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

    // Create Window
    sdl_window.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED, screen_width,
                                      screen_height, SDL_WINDOW_SHOWN));

    if (!sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer.reset(SDL_CreateRenderer(sdl_window.get(), -1, SDL_RENDERER_ACCELERATED));

    if (!sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Load a font using SDL_ttf
    font = TTF_OpenFont(R"(fonts/arial.ttf)", 24);
    if (!font) {
        std::cerr << "Failed to load font. SDL_ttf Error: " << TTF_GetError() << "\n";
        // Handle error appropriately
    }
}


Renderer::~Renderer() {
  TTF_CloseFont(font);
  SDL_Quit();
  TTF_Quit();
}

// Render Snake
void Renderer::RenderSnake(const Snake &snake, SDL_Rect &block) {
    // Set the color for the snake's body
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xFF, 0xFF, 0xFF); // Example color: White

    // Render snake's body
    for (SDL_Point const &point : snake.body) {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer.get(), &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive) {
        SDL_SetRenderDrawColor(sdl_renderer.get(), 0x00, 0x7A, 0xCC, 0xFF); // Example color for the head
    } else {
        SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0x00, 0x00, 0xFF); // Example color if not alive
    }
    SDL_RenderFillRect(sdl_renderer.get(), &block);
}

// Render Food
void Renderer::RenderFood(const SDL_Point &food, SDL_Rect &block) {
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0xFF, 0xCC, 0x00, 0xFF); // Food color
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer.get(), &block);
}

// Render snake and food for single player
void Renderer::Render(const Snake &playerSnake, const SDL_Point &food) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer.get());

    // Render player snake's body and head
    RenderSnake(playerSnake, block);

    // Render food
    RenderFood(food, block);

    // Update Screen
    SDL_RenderPresent(sdl_renderer.get());
}

// Render snake, AI snake and food for player vs AI
void Renderer::Render(const Snake &playerSnake, const ai_snake &aiSnake, const SDL_Point &food) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer.get());

    // Render player snake's body and head
    RenderSnake(playerSnake, block);

    // Render AI snake's body and head
    RenderSnake(aiSnake, block);

    // Render food
    RenderFood(food, block);

    // Update Screen
    SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window.get(), title.c_str());
}


// Render the menu page
void Renderer::RenderMenu(const std::vector<std::string> &options, int selectedOption) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer.get());

    // Set text color
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // Define positions for rendering menu _options
    int xPos = screen_width / 4; // Adjust as needed
    int yPos = screen_height / 4; // Starting vertical position for the first menu option
    int optionHeight = 50; // Height between menu _options

    for (size_t i = 0; i < options.size(); i++) {
        if (i == selectedOption) {
            // Highlight the selected option, e.g., by changing its color
            textColor = {255, 255, 0, 255}; // Yellow color for selected option
        } else {
            textColor = {255, 255, 255, 255}; // White color for non-selected _options
        }

        // Create surface from text
        SDL_Surface *surface = TTF_RenderText_Solid(font, options[i].c_str(), textColor);
        if (surface == nullptr) {
            std::cerr << "Unable to create text surface. SDL_ttf Error: " << TTF_GetError() << "\n";
            continue;
        }

        // Create texture from surface
        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer.get(), surface);
        if (texture == nullptr) {
            std::cerr << "Unable to create texture from surface. SDL Error: " << SDL_GetError() << "\n";
        }

        SDL_Rect renderQuad = {xPos, yPos + (int)i * optionHeight, surface->w, surface->h};
        SDL_RenderCopy(sdl_renderer.get(), texture, nullptr, &renderQuad);

        // Clean up surface and texture
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    // Update Screen
    SDL_RenderPresent(sdl_renderer.get());
}

// Render the name input page
void Renderer::RenderNameInput(const std::string &currentInput) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer.get());

    // Set text color
    SDL_Color textColor = {255, 255, 255, 255}; // White color

    // Handle empty input (show placeholder or cursor)
    std::string displayText = currentInput.empty() ? "Enter Name: _" : currentInput;

    // Create surface from the current input text
    SDL_Surface *surface = TTF_RenderText_Solid(font, displayText.c_str(), textColor);
    if (surface == nullptr) {
        std::cerr << "Unable to create text surface. SDL_ttf Error: " << TTF_GetError() << "\n";
    } else {
        // Create texture from surface
        SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer.get(), surface);
        if (texture == nullptr) {
            std::cerr << "Unable to create texture from surface. SDL Error: " << SDL_GetError() << "\n";
        } else {
            // Define position to render the text (centered)
            int x = (screen_width - surface->w) / 2;
            int y = (screen_height - surface->h) / 2;
            SDL_Rect renderQuad = {x, y, surface->w, surface->h};

            // Render text
            SDL_RenderCopy(sdl_renderer.get(), texture, nullptr, &renderQuad);

            // Clean up texture
            SDL_DestroyTexture(texture);
        }

        // Clean up surface
        SDL_FreeSurface(surface);
    }

    // Update Screen
    SDL_RenderPresent(sdl_renderer.get());
}

void Renderer::RenderScoreSheet(const Scoresheet& scoresheet) const {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer.get(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer.get());

    // Set text color for the title and scores
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    int xPos = screen_width / 4;
    int yPos = 50; // Starting Y position for the title
    int lineSpacing = 30; // Spacing between lines

    // Render title "Score Sheet"
    SDL_Surface* titleSurface = TTF_RenderText_Solid(font, "Score Sheet", textColor);
    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(sdl_renderer.get(), titleSurface);
    SDL_Rect titleRect = {xPos, yPos, titleSurface->w, titleSurface->h};
    SDL_RenderCopy(sdl_renderer.get(), titleTexture, nullptr, &titleRect);
    SDL_FreeSurface(titleSurface);
    SDL_DestroyTexture(titleTexture);
    yPos += titleRect.h + lineSpacing;

    // Render scores
    for (const auto& scorePair : scoresheet.getScores()) {
        std::string scoreText = scorePair.first + ": " + std::to_string(scorePair.second);
        SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
        SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(sdl_renderer.get(), scoreSurface);
        SDL_Rect scoreRect = {xPos, yPos, scoreSurface->w, scoreSurface->h};
        SDL_RenderCopy(sdl_renderer.get(), scoreTexture, nullptr, &scoreRect);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(scoreTexture);
        yPos += scoreRect.h + lineSpacing;
    }

    // Update Screen
    SDL_RenderPresent(sdl_renderer.get());
}
