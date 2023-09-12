#include <SDL2/SDL.h>

int main(int argc, char **argv) {

    // initializes SDL2
    SDL_Init(SDL_INIT_VIDEO);

    // Creating window and renderer
    SDL_Window *Window = SDL_CreateWindow("My window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600, 0);
    SDL_Renderer *Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Creating a rectangle
    SDL_Rect rect1 = {50, 50, 30, 30};

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // taking input from user
        SDL_PollEvent(&event);

        // handling input
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                rect1.x += 10;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                rect1.x -= 10;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
                rect1.y -= 10;
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
                rect1.y += 10;
            }
        }

        // drawing
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 0);
        SDL_RenderClear(Renderer);          // clears background

        SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(Renderer, &rect1);   // draws rectangle

        SDL_RenderPresent(Renderer);       // swaps buffers (basically screen is updated with new stuff now)
    }

    // destroys everything
    SDL_DestroyWindow(Window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
    return 0;
}