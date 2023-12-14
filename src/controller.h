#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "renderer.h"
#include "menu.h"

class Controller {
public:
    int HandleInput(int &game_running, Snake &snake) const;

    void UpdateMenu(Renderer &screenRender, Menu &menu);

    void UpdateNameInput(std::string &playerName, bool &nameEntered);

private:
    void ChangeDirection(Snake &snake, Snake::Direction input,
                   Snake::Direction opposite) const;
};

#endif