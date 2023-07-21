#ifndef R_SDL_H
#define R_SDL_H

#include "SDL.h"
#include "SDL_image.h"

#include "r_image.h"
#include "engine/e_app.h"
#include "defs/d_common.h"

DLLINCLUDE u32 SDL_GetPixel(SDL_Surface *src, u32 x, u32 y);
DLLINCLUDE void SDL_SetPixel(SDL_Surface *src, u32 x, u32 y, u32 rgba);
DLLINCLUDE void SDL_BlitRotated(SDL_Surface *src, SDL_Surface *dst, u32 dstX, u32 dstY);

DLLINCLUDE int SDL_BlitImage(App_t ooc, Image_t *atlasimg, u32 x, u32 y, u8 center);

DLLINCLUDE u8 *CreateMissingTextureArray(u32 w, u32 h);
DLLINCLUDE SDL_Surface *SDL_CreateMissingTexture(App_t ooc, u32 w, u32 h, u8 *px);
DLLINCLUDE Error_t SDL_DestroyMissingTexture(SDL_Surface *surf, u8 *px);

#endif
