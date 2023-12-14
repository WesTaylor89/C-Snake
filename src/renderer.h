#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include "SDL.h"
#include "snake.h"
#include "ai_snake.h"
#include <SDL2/SDL_ttf.h>

class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
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

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;

    TTF_Font *font; // font to be used

};

#endif