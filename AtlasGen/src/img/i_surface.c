#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"
#include "oocdll.h"

#include "i_surface.h"

// thank you to github user tronkko for making dirent.h for windows
// windows's file directory functions suck
// and literally every tutorial uses linux/posix/boost's DIR functions

int simg_countimg(const char *dpath) {
    DIR *d;
    struct dirent *dent;
    char *path;
    int numimgs = 0;

    if ((d = opendir(dpath)) != NULL) {
        while ((dent = readdir(d)) != NULL) {
            if (dent->d_type == DT_DIR) {
                if (dent->d_name[0] != '.') {
                    Size_t tmpsize = strlen(dpath) + strlen(dent->d_name) + 2;
                    char *path_tmp = (char *) malloc(tmpsize);
                    if (path_tmp) {
                        path = path_tmp;
                        sprintf_s(path, tmpsize, "%s/%s", dpath, dent->d_name);
                        numimgs += simg_countimg(path);
                        free(path);
                    }
                    else {
                        printf("no malloc space for simg_countimg\n");
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

void simg_loadimg(int *imgnum, const char *dir, SurfaceImage_t *imgarr) {
    DIR *d;
    struct dirent *dent;
    char *path;

    if ((d = opendir(dir)) != NULL) {
        while ((dent = readdir(d)) != NULL) {
            Size_t tmpsize = strlen(dir) + strlen(dent->d_name) + 2;
            char *path_tmp = (char *) malloc(tmpsize);
            if (path_tmp) {
                path = path_tmp;
                if (dent->d_type == DT_DIR) {
                    if (dent->d_name[0] != '.') {
                        sprintf_s(path, tmpsize, "%s/%s", dir, dent->d_name);
                        simg_loadimg(imgnum, path, imgarr);
                    }
                }
                else {
                    sprintf_s(path, tmpsize, "%s/%s", dir, dent->d_name);

                    imgarr[*imgnum].surf = IMG_Load(path);

                    if (imgarr[*imgnum].surf) {
                        imgarr[*imgnum].fpath = str_new(path);
                        SDL_SetSurfaceBlendMode(imgarr[*imgnum].surf, SDL_BLENDMODE_NONE);
                        *imgnum += 1;
                    }
                }
                free(path);
                closedir(d);
            }
            else {
                printf("no malloc space for simg_loadimg\n");
                closedir(d);
                return;
            }
        }
    }
}

int simg_imgcmp(const void *a, const void *b) {
    SurfaceImage_t *simga = (SurfaceImage_t *) a;
    SurfaceImage_t *simgb = (SurfaceImage_t *) b;

    return simgb->surf->h - simga->surf->h;
}