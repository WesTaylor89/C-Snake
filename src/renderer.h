#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include "SDL.h"
#include "snake.h"
#include "ai_snake.h"
#include "scoresheet.h"
#include <SDL2/SDL_ttf.h>
#include <memory>

// The Renderer class uses the SDL2 library to render the game window, snake, food, scoreboard and name input
class Renderer {
public:
    Renderer(std::size_t screen_width,
             std::size_t screen_height,
             std::size_t grid_width,
             std::size_t grid_height);
    ~Renderer();

    void RenderSnake(Snake const &snake, SDL_Rect &block);
    void RenderFood(const SDL_Point &food, SDL_Rect &block);

    void Render(Snake const &snake, SDL_Point const &food);
    // Overload render function to render AI snake
    void Render(const Snake &snake, const ai_snake &ai_snake, const SDL_Point &food);
    void UpdateWindowTitle(int score, int fps);
    void RenderMenu(const std::vector<std::string> &options, int selectedOption);
//    void RenderEnterNameForm();
    void RenderNameInput(const std::string &currentInput);
    void RenderScoreSheet(const Scoresheet& scoresheet) const;

private:

    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> sdl_renderer;


    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;

    TTF_Font *font; // font to be used

};

#endif