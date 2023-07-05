#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atlas/a_atlas.h"
#include "atlas/a_node.h"
#include "atlas/a_json.h"

#include "cargs/c_cmdargs.h"

#include "img/i_surface.h"

#include "oocdll.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Cmdargs_t cargs;
    cargs = cmdargs_get(argc, argv);

    // STEP 1: get how many images we need to load from disk

    i32 numimgs = 0;
    numimgs = simg_countimgs((const char *) cargs.dirpath);

    // STEP 2: load all the images from the disk and put them into a list

    ListNode_t *simglist = NULLADDR;

    for (i32 i = 0; i < numimgs; i++) {
        //simg_loadimgs(i, cargs.dirpath, simglist);

        simglist = list_addtotail(simglist, i, (void *) simg_loadimgs(i, cargs.dirpath), simg_free_fnptr, simg_cmp_fnptr);
    }

    // STEP 3: sort the images by largest first, then renumber images

    list_mergesortbydata(&simglist);
    list_renumber(simglist);

    // STEP 4: Make a new SDL surface for the output atlas image

    SDL_Surface *atlasimg = SDL_CreateRGBSurface(0, cargs.aimgsize, cargs.aimgsize, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    // STEP 5: Make a new atlas tree

    AtlasNode_t *atlastree = atlasnode_new(0, 0, cargs.aimgsize, cargs.aimgsize);

    // STEP 6: Make a new JSON file for the output atlas metadata

    cJSON *rootjson;
    rootjson = cJSON_CreateArray();

    // STEP 7: Loop through each img in list, then add to tree and add a json entry

    SDL_Rect rect;
    memset(&rect, 0, sizeof(SDL_Rect));

    AtlasNode_t *anodetmp = NULLADDR;
    ListNode_t *lnodetmp = NULLADDR;

    for (i32 i = 0; i < numimgs; i++) {

        lnodetmp = list_searchbykey(simglist, i);
        Error_t e = atlas_fitsurfimg(lnodetmp, atlastree, numimgs, i, cargs.padding, atlasimg, rect);
        if (e == ERROR_NOERROR) {
            atlas_addjsonentry(rootjson, lnodetmp, rect);
        }
    }

    // STEP 8: make a json file and dump everything we wrote into it

    char *out = cJSON_Print(rootjson);
    FILE *fptr;
    fopen_s(&fptr, "atlasdata.json", "wb");
    if (fptr) {
        fprintf(fptr, "%s", out);
        fclose(fptr);
    }

    // STEP 9: save the atlasimg sdl surface as a qoi file

    IMG_SaveQOI(atlasimg, "atlasimg.qoi");

    // STEP 10: clean up all our mess

    list_freelist(simglist);
    SDL_FreeSurface(atlasimg);
    atlasnode_freedeep(atlastree);
    cJSON_Delete(rootjson);
    free(out);
    cmdargs_free(cargs);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}