#include <stdio.h>
#include <SDL2/SDL.h>

int main(int argc, char *argv[]) {

    SDL_Init(SDL_INIT_EVERYTHING);

    int width = 800;
    int height = 600;

    SDL_Window *wdw = SDL_CreateWindow("OoC SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

    if (wdw == NULL) {
        printf("dammit, %s\n", SDL_GetError());
        return 1;
    }

    SDL_Event evt;

    while (1) {
        if (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                break;
            }
        }
    }
    
    SDL_DestroyWindow(wdw);
    SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
    SDL_Quit();

    return 0;
}