#ifndef R_SDL_H
#define R_SDL_H

#ifdef OOCDLL_EXPORTS
#define R_SDL_API __declspec(dllexport)
#else
#define R_SDL_API __declspec(dllimport)
#endif

#include "SDL.h"
#include "SDL_image.h"
#include "qoi.h"

#include "defs/d_common.h"

#define SDL_SaveQOI(sur, dst) SDL_SaveQoi_RW(sur, SDL_RWFromFile(dst, "wb"), 1)

R_SDL_API u32 SDL_GetPixel(SDL_Surface *src, u32 x, u32 y);
R_SDL_API void SDL_SetPixel(SDL_Surface *src, u32 x, u32 y, u32 rgba);
R_SDL_API void SDL_BlitRotated(SDL_Surface *src, SDL_Surface *dst, u32 dstX, u32 dstY);

R_SDL_API int SDL_SaveQoi_RW(SDL_Surface *surf, SDL_RWops *dst, int freedst);

#endif
