#include <iostream>
#include "Window_Object.h"
#include "Player_Object.h"
#include "Map_Object.h"

int main(int argc, char **argv) {
    // initializing stuff
    SDL_Init(SDL_INIT_VIDEO);

    Window_Object *win_obj = new Window_Object("Pacman", 975, 775);
    Player_Object *player = new Player_Object(26, 26, 24, 24, win_obj->Renderer);

    Map_Object *map = new Map_Object(25, 25, win_obj->Renderer);

    SDL_Event event;
    while (!win_obj->quit) {
        // taking input from user
        SDL_PollEvent(&event);

        // handling input
        win_obj->handle_input(event);
        player->handle_input(event);

        // update
        player->update(map);
        map->handle_collision(player->rect, player->old_x, player->old_y);

        // drawing
        win_obj->clear_background();  // clears background
        map->draw();                  // draws map
        player->draw();               // draws player
        win_obj->swap_buffer();       // swaps buffers
    }

    // destroys everything
    delete win_obj;
    delete player;
    delete map;
    SDL_Quit();

    return 0;
}
