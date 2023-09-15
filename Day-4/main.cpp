#include <SDL2/SDL.h>
#include "Window_Object.h"
#include "Player_Object.h"
#include "Map_Object.h"

int main(int argc, char **argv) {

    // initializing stuff
    SDL_Init(SDL_INIT_VIDEO);

    Window_Object *win_obj = new Window_Object("My Game", 900, 600);
    Player_Object *player = new Player_Object(50, 50, 50, 50, win_obj->Renderer);
    Map_Object *map = new Map_Object(50, 50, win_obj->Renderer);

    SDL_Event event;
    while (!win_obj->quit) {
        // taking input from user
        SDL_PollEvent(&event);

        // handling input
        win_obj->handle_input(event);
        player->handle_input(event);

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
