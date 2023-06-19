#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"
#include "oocdll.h"

#include "windows.h"

#include "img/i_node.h"
#include "img/i_surface.h"
#include "cargs/c_cmdargs.h"

int main(int argc, char *argv[]) {
    Cmdargs_t argvs;
    argvs = cmdargs_get(argc, argv);

    SurfaceImage_t *images = NULLADDR;

    SDL_Init(SDL_INIT_VIDEO);

    int numimg = 0;
    // numimg = agen_getnumimgs();

    for (int i = 0; i < numimg; i++) {
        printf("[%003d / %003d] %s\n", i + 1, numimg, images[i].fpath);
        atlas_add(images[i]);
        SDL_FreeSurface(images[i].surf);
        free(images[i].fpath);
    }

    free(images);
    free(argvs.dirpath);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}