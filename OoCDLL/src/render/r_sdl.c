#include "r_sdl.h"

#include "qoi.h"
#include "SDL.h"
#include "SDL_image.h"

u32 SDL_GetPixel(SDL_Surface *src, u32 x, u32 y) {
    int bpp = src->format->BytesPerPixel;
    u8 *p = (u8 *) src->pixels + y * src->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
            break;
        case 2:
            return *(u16 *) p;
            break;
        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;
            break;
        case 4:
            return *(u32 *) p;
            break;
        default:
            return 0;
    }
}

void SDL_SetPixel(SDL_Surface *src, u32 x, u32 y, u32 rgba) {
    u32 *const tgtpx = (u32 *) ((u8 *) src->pixels + y * src->pitch + x * src->format->BytesPerPixel);
    *tgtpx = rgba;
}


void SDL_BlitRotated(SDL_Surface *src, SDL_Surface *dst, u32 dstX, u32 dstY) {
    i32 x, y, p, dx, dy;
    dy = 0;

    for (x = 0; x < src->w; x++) {
        dx = src->h - 1;

        for (y = 0; y < src->h; y++) {
            p = SDL_GetPixel(src, x, y);
            SDL_SetPixel(dst, dstX + x, dstY + y, p);
            dx--;
        }
        dy++;
    }
}

int SDL_SaveQOI_RW(SDL_Surface *surf, SDL_RWops *dst, int freedst) {
    SDL_bool hasalp = (surf->format->Amask != 0);
    u32 format = hasalp ? SDL_PIXELFORMAT_RGBA32 : SDL_PIXELFORMAT_RGB24;
    int channels = hasalp ? 4 : 3;

    SDL_Surface *convsurf = SDL_ConvertSurfaceFormat(surf, format, 0);
    if (convsurf == NULL) {
        return 1;
    }

    qoi_desc desc = {
        .width = convsurf->w,
        .height = convsurf->h,
        .channels = channels,
        .colorspace = QOI_SRGB
    };

    int size = 0;
    void *px = qoi_encode(convsurf->pixels, &desc, &size);
    if (px == NULL) {
        SDL_SetError("Unable to encode QOI data.");
        SDL_FreeSurface(convsurf);
        if (freedst) {
            SDL_RWclose(dst);
        }
        return 1;
    }

    Size_t res = SDL_RWwrite(dst, px, 1, size);

    SDL_free(px);
    SDL_FreeSurface(convsurf);
    if (freedst) {
        SDL_RWclose(dst);
    }

    return res != size;
}