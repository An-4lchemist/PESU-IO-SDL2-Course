#include <iostream>
#include "Window_Object.h"
#include "Player_Object.h"
#include "Map_Object.h"
#include "Pellets_Object.h"
#include <SDL2/SDL_ttf.h>

void draw_text(std::string msg, int x, int y, TTF_Font *font, SDL_Color color, SDL_Renderer *Renderer) {
    SDL_Surface *text_on_surface = TTF_RenderText_Solid(font, msg.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer, text_on_surface);

    int texW = 0, texH = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);
    SDL_Rect dstRect = {x, y, texW, texH};
    SDL_RenderCopy(Renderer, texture, nullptr, &dstRect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(text_on_surface);
}

int main(int argc, char **argv) {
    // initializing stuff
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("arial.ttf", 25);
    SDL_Color fontColor = {255, 255, 255, 255};

    Window_Object *win_obj = new Window_Object("Pacman", 975, 775);
    Player_Object *player = new Player_Object(26, 26, 24, 24, win_obj->Renderer);
    Map_Object *map = new Map_Object(25, 25, win_obj->Renderer);
    Pellets_Object *pellets = new Pellets_Object(map->get_pellets(), win_obj->Renderer);

    SDL_Event event;

    int start_time = SDL_GetTicks();
    int lag = 0;
    int time_per_frame = 16;

    int score = 0;
    bool restart = false;

    while (!win_obj->quit) {
        if (restart && player->State == Player_Object::ALIVE) {
            restart = false;
            pellets->pellets.clear();
            pellets->pellets = map->get_pellets();
        }

        // taking input from user
        SDL_PollEvent(&event);

        // handling input
        win_obj->handle_input(event);
        player->handle_input(event);

        // update
        int end_time = SDL_GetTicks();
        int dt = end_time - start_time;
        lag += dt;
        while (lag >= time_per_frame) {
            lag -= time_per_frame;

            // update
            player->update(map);
            map->handle_collision(player->rect, player->old_x, player->old_y);
            pellets->update(player->rect, score);

            if (!restart && pellets->is_empty()) {
                player->transition(Player_Object::DEAD);
                restart = true;
            }
        }
        start_time = SDL_GetTicks();

        // drawing
        win_obj->clear_background();  // clears background
        map->draw();                  // draws map
        pellets->draw();              // draws pellets
        player->draw();               // draws player
        draw_text("score: " + std::to_string(score),
                  map->cell_width * map->cols + 10, 0,
                  font, fontColor, win_obj->Renderer);
        win_obj->swap_buffer();       // swaps buffers
    }

    // destroys everything
    delete win_obj;
    delete player;
    delete pellets;
    delete map;
    SDL_Quit();
    TTF_Quit();

    return 0;
}
