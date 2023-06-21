//#include <stdio.h>
//#include <stdlib.h>

//#include "SDL.h"
//#include "SDL_image.h"
//#include "oocdll.h"

//#include "atlas/a_node.h"
//#include "atlas/a_atlas.h"
//#include "img/i_surface.h"
//#include "cargs/c_cmdargs.h"

int main(int argc, char *argv[]) {
 /*
    Cmdargs_t cargs;
    AtlasNode_t *headnode;
    Atlas_t *atlas;
    SurfaceImage_t **imgarr;
    SurfaceImage_t ***imgarrptr;
    SDL_Rect dest;
    cJSON *headjson, *tailjson;
    String_t jsonfname;
    FILE *f;
    int numimgs;

    SDL_Init(SDL_INIT_VIDEO);

    cargs = cmdargs_get(argc, argv);

    headnode = node_new(0, 0, cargs.aimgsize, cargs.aimgsize);

    atlas = atlas_new(cargs.aimgsize, cargs.aimgsize, cargs.dirpath, "\\atlases\\atlas.qoi");

    jsonfname = str_new("");
    str_append(&jsonfname, cargs.dirpath);
    str_append(&jsonfname, "\\atlases\\atlas.json");

    headjson = cJSON_CreateArray();

    numimgs = simg_countimgs(cargs.dirpath);

    imgarrptr = simg_imginit(imgarr, numimgs);

    for (int i = 0; i < numimgs; i++) {
        simg_loadimgs(i, cargs.dirpath, imgarrptr);
    }
    simg_sortimgs(imgarrptr, numimgs);

    for (int i = 0; i < numimgs; i++) {
        memset(&dest, 0, sizeof(SDL_Rect));
        if (atlas_add(atlas, headnode, &images[i], dest, cargs.padding)) {

            tailjson = cJSON_CreateObject();

            cJSON_AddStringToObject(tailjson, "f", images[i].fpath);
            cJSON_AddNumberToObject(tailjson, "x", dest.x);
            cJSON_AddNumberToObject(tailjson, "y", dest.y);
            cJSON_AddNumberToObject(tailjson, "w", dest.w);
            cJSON_AddNumberToObject(tailjson, "h", dest.h);
            cJSON_AddNumberToObject(tailjson, "r", images[i].isrotated);

            cJSON_AddItemToArray(headjson, tailjson);
        }

    }
    
    char *json = cJSON_Print(headjson);

    if (fopen_s(&f, jsonfname, "wb") != 0) {
        if (f) {
            fprintf(f, "%s", json);
            fclose(f);
        }
    }

    IMG_SaveQOI(atlas->surf, atlas->fpath);

    simg_freedeep(images, numimgs);
    atlas_free(atlas);
    node_freedeep(headnode);
    str_free(jsonfname);
    free(json);
    cJSON_Delete(headjson);
    str_free(cargs.dirpath);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

*/
    return 0;
}

/*
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
*/