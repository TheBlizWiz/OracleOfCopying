#include <string.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_image.h"

#include "r_image.h"
#include "defs/d_common.h"
#include "defs/d_constants.h"
#include "defs/d_utils.h"

/*
Error_t img_new(Image_t *imgptr, App_t ooc, const char *fpath, u32 posx, u32 posy, u32 imgw, u32 imgh) {
    if (imgptr) {
        return (Error_t) ERROR_ISNOTNULLADDR;
    }

    imgptr = (Image_t *) malloc(sizeof(Image_t *));
    if (!imgptr) {
        return (Error_t) ERROR_MALLOC_NOSPACE;
    }

    imgptr->tex = IMG_LoadTexture(ooc.rdr, fpath);
    if (!imgptr->tex) {
        printf("couldn't load texture %s: %s\n", fpath, SDL_GetError());
        return (Error_t) ERROR_SDL_GENERIC;
    }

    imgptr->rect = (SDL_Rect){
        posx,
        posy,
        imgw,
        imgh
    };

    return (Error_t) ERROR_NOERROR;
}

Error_t img_newdefault(Image_t *imgptr, App_t ooc, const char *fpath) {
    if (imgptr) {
        return (Error_t) ERROR_ISNOTNULLADDR;
    }

    imgptr = (Image_t *) malloc(sizeof(Image_t *));
    if (!imgptr) {
        return (Error_t) ERROR_MALLOC_NOSPACE;
    }

    imgptr->tex = IMG_LoadTexture(ooc.rdr, fpath);
    if (!imgptr->tex) {
        printf("couldn't load texture %s: %s\n", fpath, SDL_GetError());
        return (Error_t) ERROR_SDL_GENERIC;
    }

    imgptr->rect = (SDL_Rect){
        IMG_POS_X,
        IMG_POS_Y,
        IMG_SIZE_X,
        IMG_SIZE_Y
    };

    return (Error_t) ERROR_NOERROR;
}

Error_t img_render(Image_t *imgptr, App_t ooc, u32 posx, u32 posy) {
    if (!imgptr) {
        return (Error_t) ERROR_ISNULLADDR;
    }

    imgptr->rect.x = posx;
    imgptr->rect.y = posy;

    if (SDL_RenderCopy(ooc.rdr, imgptr->tex, NULLADDR, &imgptr->rect) < 0) {
        printf("couldn't render image at (%d, %d): %s\n", posx, posy, SDL_GetError());
        return ERROR_SDL_GENERIC;
    }

    return ERROR_NOERROR;
}

// now that im using SDL i have to re-examine how images work
// this is the new big project coming up
// so this entire file is kinda irrelevant now
// ive commented it out in case i might need it later

/*
Image_t *img_open(String_t fpath) {
    Image_t *img;
    qoi_desc qoidesc;
    u32 *qoipixels;
    Size_t pxllen;

    qoipxls = (u32 *) qoi_read(fpath, &qoidesc, 4);
    pxllen = qoidesc.width * qoidesc.height * qoidesc.channels;


    * you may wonder why im not just putting the read pixel data into img directly
    * thats because the area where the pixels were malloc'd from qoi_decode might
    * not be next to img in memory, and its easier and more responsible to manage
    * memory when you keep your data blocks all next to each other
    * so im temporarily borrowing more memory to fit all of img, than copying the
    * pixel data into img
    * then we finally free qoipixels and call it a day


    Image_t *img = (Image_t *) malloc(sizeof(Image_t) + pxllen);

    memcpy(img->pxarr, qoipixels, pxllen);
    free(qoipixels);

    img->wdt = (u32) qoidesc.width;
    img->hgt = (u32) qoidesc.height;
    img->coldepth = (u8) qoidesc.channels;
    img->colspace = (u8) qoidesc.colorspace;
    img->pxarrlen = pxllen;

    return img;
}


Image_t *img_copy(Image_t *img_orig) {
    Image_t *img_new = (Image_t *) malloc(sizeof(img_orig));

    img_new->wdt = img_orig->wdt;
    img_new->hgt = img_orig->hgt;
    img_new->coldepth = img_orig->coldepth;
    img_new->colspace = img_orig->colspace;
    img_new->pxarrlen = img_orig->pxarrlen;

    memcpy(img_new->pxarr, img_orig->pxarr, img_orig->pxarrlen)

        return img_new;
}


  * Call this function to rotate an image while keeping the original in memory
  * Some angles (every pi/2) have a faster way to rotate that skips actually rotating pixels
  * so img_rotate will pick the best function to use automatically

Image_t img_rotate(Image_t *img, double rad) {
    if (dbl_epsilon(rad, AGL_PI_HALVES, IMG_ROT_EPSILON) || dbl_epsilon(rad, ANG_NEG_3PI_HALVES, IMG_ROT_EPSILON)) {
        return img_rt_pihalves(img);
    }

    else if (dbl_epsilon(rad, AGL_PI, IMG_ROT_EPSILON) || dbl_epsilon(rad, AGL_NEG_PI, IMG_ROT_EPSILON)) {
        return img_rt_pi(img);
    }

    else if (dbl_epsilon(rad, AGL_3PI_HALVES, IMG_ROT_EPSILON) || dbl_epsilon(rad, AGL_NEG_PI_HALVES, IMG_ROT_EPSILON)) {
        return img_rt_negpihalves(img);
    }

    else if (dbl_epsilon(rad, AGL_2PI, IMG_ROT_EPSILON) || dbl_epsilon(rad, AGL_NEG_2PI, IMG_ROT_EPSILON)) {
        return img_copy(img); // rotating by 2pi is pointless
    }

    else {
        return img_rt_other(img, rad);
    }
}


Image_t img_rt_pihalves(Image_t *img) {

}

Image_t img_rt_pi(Image_t *img) {

}

Image_t img_rt_negpihalves(Image_t *img) {

}

Image_t img_rt_other(Image_t *img, double rad) {

}

*/