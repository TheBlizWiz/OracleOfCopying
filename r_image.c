#include "r_image.h"
#include "d_common.h"
#include "d_constants.h"
#include "d_utils.h"

#include <string.h>
#include <stdlib.h>

Image_t *img_open(String_t fpath) {
    Image_t *img;
    qoi_desc qoidesc;
    u32 *qoipixels;
    Size_t pxllen;

    qoipxls = (u32 *) qoi_read(fpath, &qoidesc, 4);
    pxllen = qoidesc.width * qoidesc.height * qoidesc.channels;

   /*
    * you may wonder why im not just putting the read pixel data into img directly
    * thats because the area where the pixels were malloc'd from qoi_decode might
    * not be next to img in memory, and its easier and more responsible to manage
    * memory when you keep your data blocks all next to each other
    * so im temporarily borrowing more memory to fit all of img, than copying the
    * pixel data into img
    * then we finally free qoipixels and call it a day
    */

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

/**
  * Call this function to rotate an image while keeping the original in memory
  * Some angles (every pi/2) have a faster way to rotate that skips actually rotating pixels
  * so img_rotate will pick the best function to use automatically
  */
Image_t img_rotate(Image_t *img, double rad) {
    if(dbl_epsilon(rad, AGL_PI_HALVES, IMG_ROT_EPSILON) || dbl_epsilon(rad, ANG_NEG_3PI_HALVES, IMG_ROT_EPSILON)) {
        return img_rt_pihalves(img);
    }

    else if(dbl_epsilon(rad, AGL_PI, IMG_ROT_EPSILON) || dbl_epsilon(rad, ANG_NEG_PI, IMG_ROT_EPSILON)) {
        return img_rt_pi(img);
    }

    else if(dbl_epsilon(rad, AGL_3PI_HALVES, IMG_ROT_EPSILON) || dbl_epsilon(rad, ANG_NEG_PI_HALVES, IMG_ROT_EPSILON)) {
        return img_rt_negpihalves(img);
    }

    else if(dbl_epsilon(rad, AGL_2PI, IMG_ROT_EPSILON) || dbl_epsilon(rad, ANG_NEG_2PI, IMG_ROT_EPSILON)) {
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


