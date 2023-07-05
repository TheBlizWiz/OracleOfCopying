#include "oocdll.h"
#include "SDL.h"
#include "SDL_image.h"

#include "img/i_surface.h"
#include "a_node.h"
#include "a_atlas.h"

Atlas_t *atlas_new(u32 w, u32 h, String_t dirpath, const char *fname) {
 
    Atlas_t *atlas = (Atlas_t *) malloc(sizeof(Atlas_t));
    if (atlas) {
        atlas->w = w;
        atlas->h = h;

        Size_t tmp_size = str_getlen(dirpath) + strlen(fname);
        String_t fpath_tmp = str_newfromlen(tmp_size);
        if (fpath_tmp) {
            atlas->fpath = fpath_tmp;
            str_replace(&atlas->fpath, 0, str_getlen(dirpath), dirpath);
            str_replace(&atlas->fpath, str_getlen(dirpath), strlen(fname), fname);

            atlas->surf = SDL_CreateRGBSurface(0, w, h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
            if (atlas->surf) {
                return atlas;
            }
            else {
                errprintf("coudln't malloc atlas rgb surface...\n");
                str_free(atlas->fpath);
                free(atlas);
                return NULLADDR;
            }
        }
        else {
            errprintf("couldn't malloc atlas fpath...\n");
            free(atlas);
            return NULLADDR;
        }
    }
    else {
        errprintf("couldn't malloc atlas...\n");
        return NULLADDR;
    }
}

u8 atlas_add(Atlas_t *atlas, AtlasNode_t *head, SurfaceImage_t *img, SDL_Rect dest, u32 pad) {

    AtlasNode_t *node = atlasnode_find(head, img->w, img->h, pad);
    if (!node) {
        img->isrotated = 1;
        node = atlasnode_find(node, img->h, img->w, pad);
    }
    if (node) {
        if (img->isrotated) {
            node->h = img->w;
            node->w = img->h;
        }

        dest.x = node->x;
        dest.y = node->y;
        dest.w = node->w;
        dest.h = node->h;

        if (img->isrotated) {
            SDL_BlitRotated(img->surf, atlas->surf, dest.x, dest.y);
        }
        else {
            SDL_BlitSurface(img->surf, NULL, atlas->surf, &dest);
        }

        return 1;
    }
    else {
        errprintf("Couldn't add %s to atlas image...\n", img->fpath);
        return 0;
    }
}

void atlas_free(Atlas_t *atlas) {
    str_free(atlas->fpath);
    SDL_FreeSurface(atlas->surf);
    free(atlas);
}

Error_t atlas_fitsurfimg(ListNode_t *simgnode, AtlasNode_t *atlasroot, u32 numimgs, u32 currimg, u32 pad, SDL_Surface *atlasimg, SDL_Rect rect) {
    if (simgnode && simgnode->data) {
        SurfaceImage_t *simg = (SurfaceImage_t *) simgnode->data;
        if (simg) {

            AtlasNode_t *anodetmp = atlasnode_find(atlasroot, simg->w, simg->h, pad); // find a spot for surfimg
            
            if (!anodetmp) {
                simg->isrotated = 1;
                anodetmp = atlasnode_find(atlasroot, simg->h, simg->w, pad); // if it doesnt fit, rotate the img to the right and try again
            }

            if (anodetmp) { // found a spot for the img
                if (simg->isrotated) { // update node dims if surfimg had to be rotated to fit
                    anodetmp->h = simg->w;
                    anodetmp->w = simg->h;
                }

                rect.x = anodetmp->x; // set the output rect dimensions for the json file
                rect.y = anodetmp->y;
                rect.w = anodetmp->w;
                rect.h = anodetmp->h;

                if (!simg->isrotated) { // add the image to the output atlas image
                    SDL_BlitSurface(simg->surf, NULL, atlasimg, &rect);
                }
                else {
                    SDL_BlitRotated(simg->surf, atlasimg, rect.x, rect.y);
                }

                printf("[%04d / %04d] %s\n", currimg + 1, numimgs, simg->fpath);

                return ERROR_NOERROR;
            }
            else { // img doesnt fit
                errprintf("ERROR: No space for surface img %s in node tree. Make the image bigger...\n", simg->fpath);
                return ERROR_GENERIC;
            }
        }
        else {
            errprintf("ERROR: couldn't cast to SurfaceImage_t *\n");
            return ERROR_GENERIC;
        }
    }
    else {
        errprintf("ERROR: simgnode or simgnode->data is null\n");
        return ERROR_ISNULLADDR;
    }
}