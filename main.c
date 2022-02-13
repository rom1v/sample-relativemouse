#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

int main() {
    int r = SDL_Init(SDL_INIT_EVENTS);
    if (r) {
        fprintf(stderr, "Init failed: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

    int x = SDL_WINDOWPOS_CENTERED;
    int y = SDL_WINDOWPOS_CENTERED;
    int w = 256;
    int h = 256;
    SDL_Window *window = SDL_CreateWindow("sample", x, y, w, h, 0);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        exit(1);
    }

    // There is no rendering, so the window content will contain garbage, but
    // we don't care for this sample

    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                printf("Quit\n");
                goto end;
            case SDL_MOUSEMOTION:
                if (SDL_GetRelativeMouseMode()) {
                    printf("[relative mode] mouse motion (%d, %d)\n",
                           event.motion.xrel, event.motion.yrel);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (SDL_GetRelativeMouseMode()) {
                    printf("[relative mode] mouse button up\n");
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_GetRelativeMouseMode()) {
                    printf("[relative mode] mouse button down\n");
                }
                break;
            case SDL_KEYDOWN:
                // Toggle relative mode on Alt
                if (event.key.keysym.sym == SDLK_LALT) {
                    SDL_bool new_mode = !SDL_GetRelativeMouseMode();
                    if (new_mode) {
                        int mouse_x, mouse_y;
                        SDL_GetGlobalMouseState(&mouse_x, &mouse_y);

                        int x, y, w, h;
                        SDL_GetWindowPosition(window, &x, &y);
                        SDL_GetWindowSize(window, &w, &h);

                        SDL_SetRelativeMouseMode(SDL_TRUE);

                        if (mouse_x < x || mouse_x >= x + w ||
                                mouse_y < y || mouse_y >= y + h) {
                            SDL_WarpMouseInWindow(window, w/2, h/2);
                        }
                    } else {
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                    }
                    printf("switch relative mode to %s\n",
                           new_mode ? "true" : "false");
                }
                break;
        }
    }

end:
    SDL_DestroyWindow(window);

    return 0;
}
