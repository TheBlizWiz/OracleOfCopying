#ifndef I_SURFACE_H
#define I_SURFACE_H

//#include "SDL.h"
//#include "SDL_image.h"

//#include "oocdll.h"


/*
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
    String_t fpath;
} SurfaceImage_t;

typedef struct {
    SurfaceImage_t *prev;
    SurfaceImage_t *next;
    SurfaceImage_t *simg;
} SurfImageNode_t;

Error_t simgnode_init(SurfImageNode_t *, int numimgs);



SurfaceImage_t ***simg_imginit(SurfaceImage_t **imgarray, int numimgs);
void simg_sortimgs(SurfaceImage_t ***imgarrptr, int numimgs);
int simg_countimgs(const char *dpath);
void simg_loadimgs(int curimg, const char *dir, SurfaceImage_t ***imgarrptr);
int simg_imgcmp(const void *a, const void *b);
void simg_freedeep(SurfaceImage_t *images, int numimgs);
*/

#endif