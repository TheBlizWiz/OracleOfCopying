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
    u8 isrotated;
    SDL_Rect rect; // for the json file only, TODO: we dont need w and h since its in SDL_Rect so go back and redo it all
    String_t fpath;
} SurfaceImage_t;

SurfaceImage_t *simg_new(SDL_Surface *surf, u32 w, u32 h, u8 isrotated, String_t fpath);
Error_t simg_free_fnptr(const void *SurfaceImage_t_simg);
i32 simg_cmp_fnptr(const void *SurfaceImage_t_A, const void *SurfaceImage_t_B);
i32 simg_countimgs(const char *dpath);
void simg_loadimgs(i32 *curimg, const char *dir, ListNode_t **head);

#endif