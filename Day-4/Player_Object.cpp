#include "Player_Object.h"

Player_Object::Player_Object(int x, int y, int w, int h, SDL_Renderer *Renderer)
        : Renderer(Renderer) {
    rect = {x, y, w, h};
}

void Player_Object::handle_input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            rect.x += 10;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            rect.x -= 10;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            rect.y -= 10;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            rect.y += 10;
        }
    }
}

void Player_Object::draw() {
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(Renderer, &rect);
}


