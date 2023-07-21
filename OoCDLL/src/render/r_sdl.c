#include "r_sdl.h"
#include "defs/d_constants.h"

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

int SDL_BlitImage(App_t ooc, Image_t *img, u32 x, u32 y, u8 center) {

    SDL_Rect dest;
    SDL_Point p;
    zeroset(&dest, sizeof(SDL_Rect));
    zeroset(&p, sizeof(SDL_Point));

    if (img) {

        dest.x = x;
        dest.y = y;
        dest.w = img->rect.w;
        dest.h = img->rect.h;

        p.x = 0;
        p.y = 0;

        if (img->isrotated) {
            if (center) {
                dest.x -= (dest.w >> 1);
                dest.y -= (dest.h >> 1);
            }

            return SDL_RenderCopy(ooc.rdr, img->tex, &img->rect, &dest);
        }
        else {
            if (center) {
                dest.x -= (dest.h >> 1);
                dest.y -= (dest.w >> 1);
            }

            dest.y += img->rect.w;

            return SDL_RenderCopyEx(ooc.rdr, img->tex, &img->rect, &dest, ANGLE_NEG_90, &p, SDL_FLIP_NONE);
        }
    }
    else {
        // for one reason or another, img is null
        // rather than do some test like "is this texture really needed"
        // or do some error handling multiple levels down
        // lets instead just make a missing texture Image_t on the spot
        // and render that instead

        // edit: so after looking into why i was getting memory leaks it
        // turns out that i cant just make a new missing texture on the spot
        // whenever i need it because i dont ever free that missing texture...

        // ill think about it
        return ERROR_OHSHIT;
    }
}

u8 *CreateMissingTextureArray(u32 w, u32 h) {
    u8 magenta[4] = { 0xFF, 0xFF, 0x00, 0xFF };
    u8 black[4] = { 0x00, 0x00, 0x00, 0xFF };

    u8 *px;
    px = (u8 *) malloc(sizeof(u8) * w * h * 4);
    if (px) {

        u32 i = 0;
        while (i < (w * h * 4)) {
            u32 x = i / 4 / h;
            u32 y = i / 4 % h;

            if ((x < (w / 2)) && (y < (h / 2))) {
                px[i + 0] = magenta[0];
                px[i + 1] = magenta[1];
                px[i + 2] = magenta[2];
                px[i + 3] = magenta[3];
            }
            if ((x < (w / 2)) && (y >= (h / 2))) {
                px[i + 0] = black[0];
                px[i + 1] = black[1];
                px[i + 2] = black[2];
                px[i + 3] = black[3];
            }
            if ((x >= (w / 2)) && (y < (h / 2))) {
                px[i + 0] = black[0];
                px[i + 1] = black[1];
                px[i + 2] = black[2];
                px[i + 3] = black[3];
            }
            if ((x >= (w / 2)) && (y >= (h / 2))) {
                px[i + 0] = magenta[0];
                px[i + 1] = magenta[1]; // intellisense you absolute moron
                px[i + 2] = magenta[2];
                px[i + 3] = magenta[3];
            }

            i += 4;
        }
        return px;
    }
    else {
        errprintf("ERROR: no malloc space for pixels for new missing texture\n");
        return NULLADDR;
    }
}

SDL_Surface *SDL_CreateMissingTexture(App_t ooc, u32 w, u32 h, u8 *px) {


        SDL_Surface *surf = SDL_CreateRGBSurfaceWithFormatFrom((void *) *px, w, h, 8, sizeof(u8) * w * 4, SDL_PIXELFORMAT_RGBA8888);
        if(surf) {
            return surf;
        }
        else {
            errprintf("SDL ERROR: %s\n", SDL_GetError());
            return NULLADDR;
        }


}

Error_t SDL_DestroyMissingTexture(SDL_Surface *surf, u8 *px) {
    if (surf && px) {
        SDL_FreeSurface(surf);
        free(px);
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: missingtex or pixel array is null, can't free\n");
        return ERROR_ISNULLADDR;
    }
}