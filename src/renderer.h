#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <vector>
#include "SDL.h"
#include "snake.h"
#include <SDL2/SDL_ttf.h>

class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(Snake const snake, SDL_Point const &food);
    void UpdateWindowTitle(int score, int fps);
    void RenderMenu(const std::vector<std::string> &options, int selectedOption);
//    void RenderEnterNameForm();
    void RenderNameInputForm(const std::string &currentInput);

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