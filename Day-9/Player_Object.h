#ifndef SDL2_TEST_PLAYER_OBJECT_H
#define SDL2_TEST_PLAYER_OBJECT_H

#include <SDL2/SDL.h>
#include "Map_Object.h"

class Player_Object {
public:

    SDL_Rect rect;
    SDL_Renderer *Renderer;

    int old_x;
    int old_y;
    int speed = 10;

    bool move_left{};
    bool move_up{};
    bool move_down{};
    bool move_right{};

    enum States{
        ALIVE, DEAD
    }State = ALIVE;

    Player_Object(int x, int y, int w, int h, SDL_Renderer *Renderer);

    void handle_input(SDL_Event event);

    void update(Map_Object *map);

    void draw();
};

#endif //SDL2_TEST_PLAYER_OBJECT_H

