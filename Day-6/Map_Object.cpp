#include "Map_Object.h"

Map_Object::Map_Object(int cell_w, int cell_h, SDL_Renderer *Renderer)
        : Renderer(Renderer), cell_height(cell_h), cell_width(cell_w) {

    SDL_Surface *dummy = IMG_Load("map.png");
    Map_Texture = SDL_CreateTextureFromSurface(Renderer, dummy);
    SDL_FreeSurface(dummy);

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

Map_Object::~Map_Object() {
    SDL_DestroyTexture(Map_Texture);
}

void Map_Object::draw() {
//    SDL_SetRenderDrawColor(Renderer, 0, 0, 255, 255);
//    for (auto rect: walls) {
//        SDL_RenderFillRect(Renderer, &rect);
//    }
    SDL_Rect dstRect = {0, 0, cell_width * cols, cell_height * rows};
    SDL_RenderCopy(Renderer, Map_Texture, nullptr, &dstRect);
}

void Map_Object::handle_collision(SDL_Rect &rect, int old_x, int old_y) {
    for (auto wall: walls) {
        if (SDL_HasIntersection(&wall, &rect)) {
            if (rect.x > old_x) {
                rect.x = wall.x - rect.w;
            } else if (rect.x < old_x) {
                rect.x = wall.x + wall.w;
            } else if (rect.y > old_y) {
                rect.y = wall.y - rect.h;
            } else if (rect.y < old_y) {
                rect.y = wall.y + wall.h;
            }
            break;
        }
    }
}

bool Map_Object::is_wall(int x_index, int y_index) {
    if (!(0 <= x_index <= cols))
        return false;
    if (!(0 <= y_index <= rows))
        return false;
    return (tile_map[y_index][x_index] == 1);
}
