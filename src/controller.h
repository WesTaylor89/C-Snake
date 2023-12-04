#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "renderer.h"
#include "menu.h"

class Controller {
public:
    void HandleInput(bool &running, Snake &snake) const;

    void Update(Renderer &screenRender, Menu &menu);

private:
    void ChangeDirection(Snake &snake, Snake::Direction input,
                   Snake::Direction opposite) const;
};

#endif