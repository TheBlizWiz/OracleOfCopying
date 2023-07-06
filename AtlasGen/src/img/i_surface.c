#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_image.h"
#include "oocdll.h"

#include "stb_image.h"

#include "i_surface.h"

// thank you to github user tronkko for making dirent.h for windows
// windows's file directory functions suck
// and literally every tutorial uses linux/posix/boost's DIR functions


SurfaceImage_t *simg_new(SDL_Surface *surf, u32 w, u32 h, u8 isrotated, String_t fpath) {
    SurfaceImage_t *simg = (SurfaceImage_t *) malloc(sizeof(SurfaceImage_t));
    if (simg) {
        simg->surf = surf;
        simg->w = w;
        simg->h = h;
        simg->isrotated = isrotated;
        simg->rect = (SDL_Rect){ .x = 0, .y = 0, .w = 0, .h = 0 };
        simg->fpath = fpath;
        return simg;
    }
    else {
        return NULLADDR;
    }
}

Error_t simg_free_fnptr(const void *SurfaceImage_t_simg) {
    if (SurfaceImage_t_simg) {
        SurfaceImage_t *simg = (SurfaceImage_t *) SurfaceImage_t_simg;
        if (simg) {
            str_free(simg->fpath);
            SDL_FreeSurface(simg->surf);
            free(simg);
            return ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: couldn't cast to SurfaceImage_t *\n");
            return ERROR_GENERIC;
        }
    }
    else {
        errprintf("ERROR: void * ptr to SurfaceImage_t is null\n");
        return ERROR_ISNULLADDR;
    }
}

i32 simg_cmp_fnptr(const void *SurfaceImage_t_A, const void *SurfaceImage_t_B) {
    SurfaceImage_t *simga = (SurfaceImage_t *) SurfaceImage_t_A;
    SurfaceImage_t *simgb = (SurfaceImage_t *) SurfaceImage_t_B;

    return simgb->surf->h - simga->surf->h;
}

i32 simg_countimgs(const char *dpath) {
    DIR *d;
    struct dirent *dent;
    char *path;
    i32 numimgs = 0;

    if ((d = opendir(dpath)) != NULL) {
        while ((dent = readdir(d)) != NULL) {
            if (dent->d_type == DT_DIR) {
                if (dent->d_name[0] != '.') {
                    Size_t tmpsize = strlen(dpath) + strlen(dent->d_name) + 2;
                    path = (char *) malloc(tmpsize);
                    if (path) {
                        sprintf_s(path, tmpsize, "%s/%s", dpath, dent->d_name);
                        numimgs += simg_countimgs(path);
                        free(path);
                    }
                    else {
                        errprintf("ERROR: no malloc space for simg_countimg\n");
                        closedir(d);
                        return -1;
                    }
                }
            }
            else {
                numimgs++;
            }
        }
        closedir(d);
    }

    return numimgs;
}



void simg_loadimgs(i32 *curimg, const char *dir, ListNode_t **head) { 
    DIR *d;
    struct dirent *dent;
    char *path;

    if ((d = opendir(dir)) != NULL) {
        while ((dent = readdir(d)) != NULL) {
            Size_t tmpsize = strlen(dir) + strlen(dent->d_name) + 2;
            path = (char *) malloc(tmpsize);
            if (path) {
                if (dent->d_type == DT_DIR) {
                    if (dent->d_name[0] != '.') {
                        sprintf_s(path, tmpsize, "%s/%s", dir, dent->d_name);
                        simg_loadimgs(curimg, path, head);
                    }
                }
                else {
                    sprintf_s(path, tmpsize, "%s/%s", dir, dent->d_name);

                    const char *ext = file_getextension(path);
                    if (strcmp(ext, "qoi") == 0) {

                        SDL_Surface *surf = IMG_Load(path);
                        String_t fp = str_new(path);
                        if (surf && fp) {
                            SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_NONE);
                            SurfaceImage_t *simg = simg_new(surf, surf->w, surf->h, 0, fp);
                            *head = list_addtohead(*head, *curimg, (void *) simg, simg_free_fnptr, simg_cmp_fnptr);
                            (*curimg)++;
                        }
                    }
                }
                free(path);
            }
            else {
                errprintf("ERROR: no malloc space for simg_loadimg\n");
                closedir(d);
            }
        }
        closedir(d);
    }
}

/*
void qoiconv(const char *pngfname, char *qoifname) {
    void *px = NULLADDR;
    int w, h, channels;
    
    if (stbi_info(pngfname, &w, &h, &channels)) {
        if (channels != 3) {
            channels = 4;
        }

        px = (void *) stbi_load(pngfname, &w, &h, NULLADDR, channels);

        if (px) {
            int encoded = 0;
            encoded = qoi_write(qoifname, px, &(qoi_desc){.width = w, .height = h, .channels = channels, .colorspace = QOI_SRGB});
            if (encoded) {
                free(px);
            }
            else {
                errprintf("ERROR: couldn't encode qoi image\n");
            }
        }
        else {
            errprintf("ERROR: couldnt malloc and load pixels from png image\n");
        }
    }
    else {
        errprintf("ERROR: couldn't read from png file\n");
    }
}
*/