//#include "oocdll.h"
//#include "SDL.h"
//#include "SDL_image.h"

//#include "img/i_surface.h"
//#include "a_node.h"
//#include "a_atlas.h"
/*
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
                printf("coudln't malloc atlas rgb surface...\n");
                str_free(atlas->fpath);
                free(atlas);
                return NULLADDR;
            }
        }
        else {
            printf("couldn't malloc atlas fpath...\n");
            free(atlas);
            return NULLADDR;
        }
    }
    else {
        printf("couldn't malloc atlas...\n");
        return NULLADDR;
    }
}

u8 atlas_add(Atlas_t *atlas, AtlasNode_t *head, SurfaceImage_t *img, SDL_Rect dest, u32 pad) {

    AtlasNode_t *node = node_find(head, img->w, img->h, pad);
    if (!node) {
        img->isrotated = 1;
        node = node_find(node, img->h, img->w, pad);
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
        printf("Couldn't add %s to atlas image...\n", img->fpath);
        return 0;
    }
}

void atlas_free(Atlas_t *atlas) {
    str_free(atlas->fpath);
    SDL_FreeSurface(atlas->surf);
    free(atlas);
}
*/