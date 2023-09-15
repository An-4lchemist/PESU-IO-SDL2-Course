#ifndef SDL2_TEST_MAP_OBJECT_H
#define SDL2_TEST_MAP_OBJECT_H

#include <SDL2/SDL.h>
#include <vector>

class Map_Object {
public:
    SDL_Renderer *Renderer;
    int rows = 4;
    int cols = 4;
    int tile_map[4][4] = {
            {1, 0, 0, 1},
            {1, 1, 0, 1},
            {1, 0, 0, 1},
            {1, 0, 1, 1}
    };

    std::vector<SDL_Rect> walls;

    Map_Object(int cell_w, int cell_h, SDL_Renderer *Renderer);

    void draw();
};


#endif //SDL2_TEST_MAP_OBJECT_H
