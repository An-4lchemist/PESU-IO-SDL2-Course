#include <iostream>
#include "Window_Object.h"
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
    SDL_Event event;

    int start_time = SDL_GetTicks();
    int lag = 0;
    int time_per_frame = 16;

    int counter = 60000;

    while (!win_obj->quit) {
        // taking input from user
        SDL_PollEvent(&event);

        // handling input
        win_obj->handle_input(event);

        int end_time = SDL_GetTicks();
        int dt = end_time - start_time;
        lag += dt;
        while (lag >= time_per_frame) {
            lag -= time_per_frame;
            // update anything here

            if (counter < 0){
                win_obj->quit = true;
            }
        }
        start_time = SDL_GetTicks();

        // drawing
        win_obj->clear_background();  // clears background

        counter -= dt;
        draw_text(std::to_string(counter / 1000), 0, 0, font, fontColor, win_obj->Renderer);

        win_obj->swap_buffer();       // swaps buffers
    }

    // destroys everything
    delete win_obj;
    TTF_CloseFont(font);
    SDL_Quit();
    TTF_Quit();

    return 0;
}
