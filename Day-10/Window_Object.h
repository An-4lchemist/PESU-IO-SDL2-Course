#ifndef SDL2_TEST_WINDOW_OBJECT_H
#define SDL2_TEST_WINDOW_OBJECT_H

#include <SDL2/SDL.h>


class Window_Object {
public:
    SDL_Window *Window;
    SDL_Renderer *Renderer;
    bool quit;

    Window_Object(char *TITLE, int width, int height);

    void handle_input(SDL_Event event);

    void clear_background();

    void swap_buffer();

    ~Window_Object();
};

#endif //SDL2_TEST_WINDOW_OBJECT_H

