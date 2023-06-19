#ifndef I_SURFACE_H
#define I_SURFACE_H

#include "SDL.h"
#include "SDL_image.h"

#include "oocdll.h"

// these arent the same as Image_ts 
// these are for atlasgen and their job is to get the .qoi file from disk
// turn it into an SDL_Surface, do pixel manipulation if necessary, 
// get combined into the megatexture, write its data into the json file
// and then get converted into an Image_t for ooc.exe
// do not use these for regular use, SDL_Surfaces are on the CPU instead of the GPU
typedef struct {
    SDL_Surface *surf;
    u32 w;
    u32 h;
    String_t fpath;
} SurfaceImage_t;

int simg_countimg(const char *);
void simg_loadimg(int *, const char *, SurfaceImage_t *);
int simg_imgcmp(const void *, const void *);

#endif