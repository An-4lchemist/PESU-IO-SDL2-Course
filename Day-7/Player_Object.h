#ifndef SDL2_TEST_PLAYER_OBJECT_H
#define SDL2_TEST_PLAYER_OBJECT_H

#include <SDL2/SDL.h>
#include "Map_Object.h"

#define IDLE 0b000
#define LEFT 0b001
#define RIGHT 0b010
#define JUMP 0b100

class Player_Object {
public:

    SDL_Rect rect;
    SDL_Renderer *Renderer;

    int old_x{};
    int old_y{};
    int speed = 3;
    int y_vel{};
    int jump_acc = 17;
    int grav_acc = 2;
    bool is_jumping = false;

    int direction_to_move{};

    Player_Object(int x, int y, int w, int h, SDL_Renderer *Renderer);

    void handle_input(SDL_Event event);

    void update(Map_Object *map);

    void draw();
};

#endif //SDL2_TEST_PLAYER_OBJECT_H

