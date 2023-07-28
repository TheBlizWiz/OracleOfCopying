#ifndef R_SDL_H
#define R_SDL_H

#include "SDL.h"
#include "SDL_image.h"

#include "r_image.h"
#include "engine/e_app.h"
#include "defs/d_common.h"

// these functions are solely used in AtlasGen, and shouldn't be used for DgM or OoC

DLLINCLUDE u32 SDL_GetPixel(SDL_Surface *src, u32 x, u32 y);
DLLINCLUDE void SDL_SetPixel(SDL_Surface *src, u32 x, u32 y, u32 rgba);
DLLINCLUDE void SDL_BlitRotated(SDL_Surface *src, SDL_Surface *dst, u32 dstX, u32 dstY);

// this is the function you call normally. what i want is that you can add in parameters on the end and depending on what you add in it will add rotation, scaling, or flipping

DLLINCLUDE int SDL_BlitImage(App_t ooc, Image_t *img, Coordinate c, u8 center, u8 rotflipscl, ...);

// these functions below are private helper functions for SDL_BlitAtlasImage

int _SDL_blitImageEx(App_t ooc, Image_t *img, Coordinate c, u8 center, double ang, SDL_RendererFlip flip, double scl);
int _SDL_blitImage(App_t ooc, Image_t *img, Coordinate c, u8 center);

DLLINCLUDE int SDL_ColorMod(Image_t *img, Color_u color);
DLLINCLUDE int SDL_ColorReset(Image_t *img);

// these functions below are broken and dont work the way i need them to, dont use em

DLLINCLUDE u8 *CreateMissingTextureArray(u32 w, u32 h);
DLLINCLUDE SDL_Surface *SDL_CreateMissingTexture(App_t ooc, u32 w, u32 h, u8 *px);
DLLINCLUDE Error_t SDL_DestroyMissingTexture(Image_t *mtex, u8 *px);

#endif
