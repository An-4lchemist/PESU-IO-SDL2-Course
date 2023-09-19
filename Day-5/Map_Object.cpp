#include "Map_Object.h"

Map_Object::Map_Object(int cell_w, int cell_h, SDL_Renderer *Renderer)
        : Renderer(Renderer) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (tile_map[row][col] == 1) {
                SDL_Rect rect = {
                        col * cell_w,
                        row * cell_h,
                        cell_w,
                        cell_h
                };
                walls.push_back(rect);
            }
        }
    }
}

void Map_Object::draw() {
    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
    for (auto rect: walls) {
        SDL_RenderFillRect(Renderer, &rect);
    }
}

void Map_Object::handle_collision(SDL_Rect &rect, int old_x, int old_y) {
    for (auto wall: walls) {
        if (SDL_HasIntersection(&wall, &rect)) {
            if (rect.x > old_x) {
                rect.x = wall.x - rect.w;
            } else if (rect.x < old_x) {
                rect.x = wall.x + wall.w;
            } else if (rect.y > old_y){
                rect.y = wall.y - rect.h;
            } else if (rect.y < old_y) {
                rect.y = wall.y + wall.h;
            }
            break;
        }
    }
}
