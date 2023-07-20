#include <string.h>
#include <stdbool.h>

#include "libs/hashmap/hashmap.h"

#include "u_hash.h"
#include "render/r_image.h"
#include "defs/d_common.h"

#include "SDL.h"
#include "SDL_image.h"

int hash_imgcmp(const void *imgA, const void *imgB, void *imgdata) {
    const Image_t *iA = imgA;
    const Image_t *iB = imgB;
    return strncmp(iA->fname, iB->fname, MAX_FNAME_LENGTH);
}

bool hash_imgiter(const void *img, void *imgdata) {
    const Image_t *i = img;
    return true;
}

u64 hash_imghash(const void *img, u64 seed0, u64 seed1) {
    const Image_t *i = img;
    return hashmap_sip(i->fname, strnlen_s(i->fname, MAX_FNAME_LENGTH), seed0, seed1);
}

void hash_imgfree(void *img) {
    Image_t *i = img;
    SDL_DestroyTexture(i->tex);
}