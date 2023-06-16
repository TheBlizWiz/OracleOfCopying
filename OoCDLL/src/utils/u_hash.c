#include <string.h>
#include <stdbool.h>

#include "libs/hashmap/hashmap.h"

#include "u_hash.h"
#include "render/r_image.h"
#include "defs/d_common.h"

int hash_imgcmp(const void *imgA, const void *imgB, void *imgdata) {
    const Image_t *iA = imgA;
    const Image_t *iB = imgB;
    return strcmp(iA->fpath, iB->fpath);
}

bool hash_imgiter(const void *img, void *imgdata) {
    const Image_t *i = img;
    return true;
}

u64 hash_imghash(const void *img, u64 seed0, u64 seed1) {
    const Image_t *i = img;
    return hashmap_sip(i->fpath, i->fpathlen, seed0, seed1);
}