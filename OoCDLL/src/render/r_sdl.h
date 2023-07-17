#ifndef R_SDL_H
#define R_SDL_H

#include "SDL.h"
#include "SDL_image.h"
#include "qoi.h"

#include "defs/d_common.h"

DLLINCLUDE u32 SDL_GetPixel(SDL_Surface *src, u32 x, u32 y);
DLLINCLUDE void SDL_SetPixel(SDL_Surface *src, u32 x, u32 y, u32 rgba);
DLLINCLUDE void SDL_BlitRotated(SDL_Surface *src, SDL_Surface *dst, u32 dstX, u32 dstY);

#endif
