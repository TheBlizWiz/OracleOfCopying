#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atlas/a_node.h"
#include "atlas/a_json.h"

#include "cargs/c_cmdargs.h"

#include "img/i_surface.h"

#include "oocdll.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    // STEP 0: Get and Set command line arguments

    Cmdargs_t cargs;
    cargs = cmdargs_get(argc, argv);

    String_t atlasgenexepath = str_new(argv[0]);
    if (!atlasgenexepath) {
        printf("uhhhh\n");
        return 1;
    }

    Size_t pos = str_indexof(atlasgenexepath, 0, "AtlasGen.exe");
    str_remove(atlasgenexepath, pos, strlen("atlasgen.exe"));

    if (!cargs.outputpath || !cargs.dirpath) {
        printf("ERROR: failed to get directory and/or output paths\n");
        return 1;
    }

    String_t jsonpath = str_duplicate(cargs.outputpath);
    String_t atlaspath = str_duplicate(cargs.outputpath);

    str_append(&jsonpath, "\\atlasdata.json");
    str_append(&atlaspath, "\\atlasimg.png");

    if (!jsonpath || !atlaspath) {
        cmdargs_free(cargs);
        printf("ERROR: failed to set atlas and/or json output paths\n");
        return 2;
    }

    // STEP 1: run qoiconv to turn all the png files from the inputs into qoi files

    String_t qoiconvcmd1 = str_new("C:\\Windows\\System32\\cmd.exe /c \"");
    str_append(&qoiconvcmd1, atlasgenexepath);
    str_append(&qoiconvcmd1, "qoiconv.exe -dir \"");
    str_append(&qoiconvcmd1, cargs.dirpath);
    str_append(&qoiconvcmd1, "\"\"");
    system(qoiconvcmd1);


    // STEP 2: get how many images we need to load from disk

    i32 numimgs = 0;
    numimgs = simg_countimgs((const char *) cargs.dirpath);

    if (numimgs <= 0) {
        printf("ERROR: no images detected! What do you think you're doing?\n");
        cmdargs_free(cargs);
        str_free(jsonpath);
        str_free(atlaspath);
        return 3;
    }

    // STEP 3: load all the images from the disk and put them into a list

    ListNode_t *simglist = NULLADDR;

    i32 k = 0;
    simg_loadimgs(&k, cargs.dirpath, &simglist);

    // STEP 4: sort the images by largest first, then renumber images

    list_mergesortbydata(&simglist);
    list_renumber(simglist);

    // STEP 5: Make a new SDL surface for the output atlas image

    SDL_Surface *atlasimg = SDL_CreateRGBSurface(0, cargs.aimgsize, cargs.aimgsize, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    // STEP 6: Make a new atlas tree

    AtlasNode_t *atlastree = atlasnode_new(0, 0, cargs.aimgsize, cargs.aimgsize);

    // STEP 7: Make a new JSON file for the output atlas metadata

    cJSON *rootjson;
    rootjson = cJSON_CreateArray();

    // STEP 8: Loop through each img in list, then add to tree and add a json entry

    SDL_Rect rect;
    zeroset(&rect, sizeof(SDL_Rect));

    //AtlasNode_t *anodetmp = NULLADDR;
    ListNode_t *lnodetmp = NULLADDR;

    for (i32 i = 0; i < numimgs; i++) {

        lnodetmp = list_searchbykey(simglist, i);
        Error_t e = atlas_fitsurfimg(lnodetmp, &atlastree, numimgs, i, cargs.padding, atlasimg);
        if (e == ERROR_NOERROR) {
            atlas_addjsonentry(rootjson, lnodetmp);
        }
    }

    // STEP 9: make a json file and dump everything we wrote into it

    char *out = cJSON_Print(rootjson);
    FILE *fptr;
    fopen_s(&fptr, jsonpath, "wb");
    if (fptr) {
        fprintf(fptr, "%s", out);
        fclose(fptr);
    }

    // STEP 10: save the atlasimg sdl surface as a png file

    IMG_SavePNG(atlasimg, atlaspath);

    printf("\n\n\nSaved png to %s\n", atlaspath);
    printf("Saved json to %s\n", jsonpath);

    // STEP 11: run qoiconv.exe using cmd on the newly outputted .png file

    String_t qoiconvcmd2 = str_new("C:\\Windows\\System32\\cmd.exe /c \"");
    str_append(&qoiconvcmd2, atlasgenexepath);
    str_append(&qoiconvcmd2, "qoiconv.exe -dir \"");
    str_append(&qoiconvcmd2, cargs.outputpath);
    str_append(&qoiconvcmd2, "\"\"");

    system(qoiconvcmd2);

    // STEP 12: delete the .png file

    String_t delpngcmd = str_new("C:\\Windows\\System32\\cmd.exe /c \"");
    str_append(&delpngcmd, "if exist ");
    str_append(&delpngcmd, atlaspath);
    str_append(&delpngcmd, " del ");
    str_append(&delpngcmd, atlaspath);
    str_append(&delpngcmd, "\"");

    system(delpngcmd);

    // STEP 13: clean up all our mess

    list_freelist(simglist);
    SDL_FreeSurface(atlasimg);
    atlasnode_freedeep(&atlastree);
    cJSON_Delete(rootjson);
    free(out);
    str_free(jsonpath);
    str_free(atlaspath);
    str_free(atlasgenexepath);
    str_free(qoiconvcmd1);
    str_free(qoiconvcmd2);
    str_free(delpngcmd);
    cmdargs_free(cargs);

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}