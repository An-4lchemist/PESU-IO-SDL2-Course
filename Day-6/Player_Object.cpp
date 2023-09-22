#include "Player_Object.h"

Player_Object::Player_Object(int x, int y, int w, int h, SDL_Renderer *Renderer)
        : Renderer(Renderer) {
    rect = {x, y, w, h};
}

void Player_Object::handle_input(SDL_Event event) {
    old_x = rect.x;
    old_y = rect.y;
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            direction_to_move = RIGHT;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            direction_to_move = LEFT;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            direction_to_move = UP;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            direction_to_move = DOWN;
        }
    }
}

void Player_Object::update() {
    switch (direction_to_move) {
        case LEFT:
            rect.x -= speed;
            break;
        case RIGHT:
            rect.x += speed;
            break;
        case UP:
            rect.y -= speed;
            break;
        case DOWN:
            rect.y += speed;
            break;
    }
}

void Player_Object::draw() {
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(Renderer, &rect);
}


