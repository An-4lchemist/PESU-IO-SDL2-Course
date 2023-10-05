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
            move_right = true;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            move_left = true;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            move_up = true;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            move_down = true;
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            move_right = false;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            move_left = false;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            move_up = false;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
            move_down = false;
        }
    }
}

void Player_Object::update(Map_Object *map) {
    // code for movement
    switch (State) {
        case ALIVE:
            // move
            if (move_right) {
                rect.x += speed;
            }
            if (move_left) {
                rect.x -= speed;
            }
            if (move_up) {
                rect.y -= speed;
            }
            if (move_down) {
                rect.y += speed;
            }
            break;
        case DEAD:
            // do nothing
            break;
    }
}

void Player_Object::draw() {
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(Renderer, &rect);
}


