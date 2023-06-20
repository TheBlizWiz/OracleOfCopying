#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"
#include "oocdll.h"

#include "windows.h"

#include "atlas/a_node.h"
#include "atlas/a_atlas.h"
#include "img/i_surface.h"
#include "cargs/c_cmdargs.h"



int main(int argc, char *argv[]) {
    // the logic is here but with how many new and free there are here
    // i need to go through and clean all this up
    // so its commented for now

    Cmdargs_t argvs;
    argvs = cmdargs_get(argc, argv);
    if (!argvs.dirpath) {
        printf("str_new failed for argvs... exiting...\n");
        return 1;
    }
    else {
        SurfaceImage_t *images = NULLADDR;
        Atlas_t *atlas = NULLADDR;
        AtlasNode_t *head = NULLADDR;

        SDL_Init(SDL_INIT_VIDEO);

        int numimg = numimg = simg_countimg((const char *) argvs.dirpath);
        if (numimg == 0) {
            printf("no images to load... is the dirpath right? exiting program...\n");
            str_free(argvs.dirpath);
            SDL_QuitSubSystem(SDL_INIT_VIDEO);
            SDL_Quit();
            return 2;
        }
        else {
            images = (SurfaceImage_t *) malloc(sizeof(SurfaceImage_t) * numimg);
            if (!images) {
                printf("no malloc space to hold all the image data! exiting program...\n");
                str_free(argvs.dirpath);
                SDL_QuitSubSystem(SDL_INIT_VIDEO);
                SDL_Quit();
                return 3;
            }
            else {
                atlas = (Atlas_t *) malloc(sizeof(Atlas_t));
                if (!atlas) {
                    printf("no malloc space for atlas! exiting...\n");
                    str_free(argvs.dirpath);
                    free(images);
                    SDL_QuitSubSystem(SDL_INIT_VIDEO);
                    SDL_Quit();
                    return 4;
                }
                else {
                    atlas->fpath = str_newfromlen(str_getlen(argvs.dirpath) + strlen("\\atlas.qoi"));
                    if (!atlas->fpath) {
                        printf("No space to store atlas.qoi's file path... exiting...\n");
                        free(argvs.dirpath);
                        free(images);
                        free(atlas);
                        SDL_QuitSubSystem(SDL_INIT_VIDEO);
                        SDL_Quit();
                        return 5;
                    }
                    else {

                        head = node_new(0, 0, argvs.aimgsize, argvs.aimgsize);

                        if (!head) {
                            printf("no malloc space to start node tree! exiting...\n");
                            str_free(argvs.dirpath);
                            free(images);
                            str_free(atlas->fpath);
                            free(atlas);
                            SDL_QuitSubSystem(SDL_INIT_VIDEO);
                            SDL_Quit();
                            return 6;

                        }
                        else {

                            atlas->w = argvs.aimgsize;
                            atlas->h = argvs.aimgsize;
                            atlas->surf = SDL_CreateRGBSurface(0, atlas->w, atlas->h, 32, (u32) 0xFF000000, (u32) 0x00FF0000, (u32) 0x0000FF00, (u32) 0x000000FF);
                            str_replace(&atlas->fpath, 0, str_getlen(argvs.dirpath), argvs.dirpath);
                            str_replace(&atlas->fpath, str_getlen(argvs.dirpath), strlen("\\atlas.qoi"), "\\atlas.qoi");

                            for (int i = 0; i < numimg; i++) {
                                printf("[%003d / %003d] %s\n", i + 1, numimg, images[i].fpath);
                                atlas_add(atlas, head, &images[i], argvs.padding);
                                SDL_FreeSurface(images[i].surf);
                                str_free(images[i].fpath);
                            }

                            IMG_SaveQOI(atlas->surf, "E:/source/repos/OracleOfCopying/OracleOfCopying/textures/atlases/atlas.qoi");

                            free(images);
                            free(atlas);
                            free(argvs.dirpath);

                            SDL_QuitSubSystem(SDL_INIT_VIDEO);
                            SDL_Quit();
                        }
                    }
                }
            }
        }
    }

    return 0;
}