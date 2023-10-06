#include "Player_Object.h"
#include <iostream>

Player_Object::Player_Object(int x, int y, int w, int h, SDL_Renderer *Renderer)
        : Renderer(Renderer), rect({x, y, w, h}) {}

void Player_Object::handle_input(SDL_Event event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            move_right = true;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            move_left = true;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            jump = true;
        }
    }
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
            move_right = false;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
            move_left = false;
        }
        if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
            jump = false;
        }
    }
}

void Player_Object::update(Map_Object *map) {

    y_vel += grav_acc;
    if (y_vel > map->cell_height) {
        y_vel = map->cell_height - 1;
    }
    if (map->is_on_floor(rect)) {
        y_vel = 0;
        is_jumping = false;
    }
    if (map->is_below_ceil(rect) && y_vel < 0) {
        y_vel = 0;
    }

    old_x = rect.x;
    old_y = rect.y;

    if (move_left) {
        rect.x -= speed;
    }
    if (move_right) {
        rect.x += speed;
    }
    if (jump) {
        if (!is_jumping) {
            y_vel = -jump_acc;
            is_jumping = true;
        }
    }

    rect.y += y_vel;
}

void Player_Object::draw() {
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(Renderer, &rect);
}


