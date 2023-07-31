#pragma warning(disable : 26451)

#include <stdarg.h>
#include <math.h>

#include "r_sdl.h"
#include "defs/d_constants.h"
#include "defs/d_macros.h"

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

int SDL_BlitImage(App_t ooc, Image_t *img, Coordinate c, u8 center, u8 rotflipscl, ...) {
    if (img) {
        double ang;
        double scl;
        SDL_RendererFlip flip;

        switch (rotflipscl) {
            case TF_ROT:
            case TF_FLIP:
            case TF_SCL:
            case TF_ROTFLIP:
            case TF_ROTSCL:
            case TF_FLIPSCL:
            case TF_ROTFLIPSCL:
                va_list tforms;
                va_start(tforms, rotflipscl);

                switch (rotflipscl) {
                    case TF_ROT:
                        ang = va_arg(tforms, double);
                        flip = SDL_FLIP_NONE;
                        scl = 1.0;
                        break;
                    case TF_FLIP:
                        ang = 0.0;
                        flip = va_arg(tforms, SDL_RendererFlip);
                        scl = 1.0;
                        break;
                    case TF_SCL:
                        ang = 0.0;
                        flip = SDL_FLIP_NONE;
                        scl = va_arg(tforms, double);
                        break;
                    case TF_ROTFLIP:
                        ang = va_arg(tforms, double);
                        flip = va_arg(tforms, SDL_RendererFlip);
                        scl = 1.0;
                        break;
                    case TF_ROTSCL:
                        ang = va_arg(tforms, double);
                        flip = SDL_FLIP_NONE;
                        scl = va_arg(tforms, double);
                        break;
                    case TF_FLIPSCL:
                        ang = 0.0;
                        flip = va_arg(tforms, SDL_RendererFlip);
                        scl = va_arg(tforms, double);
                        break;
                    case TF_ROTFLIPSCL:
                        ang = va_arg(tforms, double);
                        flip = va_arg(tforms, SDL_RendererFlip);
                        scl = va_arg(tforms, double);
                        break;
                    case TF_NONE:
                    default:
                        ang = 0.0;
                        flip = SDL_FLIP_NONE;
                        scl = 1.0;
                }

                va_end(tforms);

                return _SDL_blitImageEx(ooc, img, c, center, ang, flip, scl);
                break;
            case TF_NONE:
            default:
                return _SDL_blitImage(ooc, img, c, center);
        }
    }
    else {
        return ERROR_ISNULLADDR;
    }
}

int _SDL_blitImageEx(App_t ooc, Image_t *img, Coordinate c, u8 center, double ang, SDL_RendererFlip flip, double scl) {
    SDL_FRect dest = { .x = (float) c.x, .y = (float) c.y, .w = (float) img->rect.w, .h = (float) img->rect.h };

    if (img) {
        if (!img->isrotated) {
            dest.w *= (float) scl;
            dest.h *= (float) scl;

            return SDL_RenderCopyExF(ooc.rdr, img->tex, &img->rect, &dest, ang, NULL, flip);
        }
        else {
            if (flip == SDL_FLIP_HORIZONTAL) {
                flip = SDL_FLIP_VERTICAL;
            }
            else if (flip == SDL_FLIP_VERTICAL) {
                flip = SDL_FLIP_HORIZONTAL;
            }

            dest.w *= (float) scl;
            dest.h *= (float) scl;
            ang -= 90.00;

            return SDL_RenderCopyExF(ooc.rdr, img->tex, &img->rect, &dest, ang, NULL, flip);
        }
    }
    else {
        return ERROR_ISNULLADDR;
    }
}

int _SDL_blitImage(App_t ooc, Image_t *img, Coordinate c, u8 center) {
    SDL_Point p = { .x = 0, .y = 0 };
    SDL_Rect dest = { .x = c.x, .y = c.y, .w = img->rect.w, .h = img->rect.h };
    if (img) {
        if (!img->isrotated) {
            if (center) {
                dest.x -= (dest.w / 2);
                dest.y -= (dest.h / 2);
            }

            return SDL_RenderCopy(ooc.rdr, img->tex, &img->rect, &dest);
        }
        else {
            if (center) {
                dest.x -= (dest.h / 2);
                dest.y -= (dest.w / 2);
            }
            dest.y += img->rect.w;

            return SDL_RenderCopyEx(ooc.rdr, img->tex, &img->rect, &dest, -90.00, &p, SDL_FLIP_NONE);
        }
    }
    else {
        return ERROR_ISNULLADDR;
    }
}

int SDL_ColorMod(Image_t *img, Color_u col) {
    int e1 = SDL_SetTextureColorMod(img->tex, col.r, col.g, col.b);
    int e2 = SDL_SetTextureAlphaMod(img->tex, col.a);
    return  e1 + e2;
}

int SDL_ColorReset(Image_t *img) {
    int e1 = SDL_SetTextureColorMod(img->tex, 0xFF, 0xFF, 0xFF);
    int e2 = SDL_SetTextureAlphaMod(img->tex, 0xFF);
    return e1 + e2;
}

Coordinate SDL_WorldPosToScreenPos(Point3 pt) {
    // TODO: we need to scale the texture as Z changes
    
    Coordinate c = { 0 };
    c.x = abs((u32) fmod(pt.x, ROOM_PX_SIZE_X));
    c.y = abs((u32) fmod(pt.y, ROOM_PX_SIZE_Y));
    return c;
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
    if (surf) {
        return surf;
    }
    else {
        errprintf("SDL ERROR: %s\n", SDL_GetError());
        return NULLADDR;
    }


}

Error_t SDL_DestroyMissingTexture(Image_t *mtex, u8 *px) {
    if (mtex && px) {
        SDL_DestroyTexture(mtex->tex);
        free(px);
        free(mtex);
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: missingtex or pixel array is null, can't free\n");
        return ERROR_ISNULLADDR;
    }
}