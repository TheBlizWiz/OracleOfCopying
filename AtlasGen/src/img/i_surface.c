#include <stdio.h>

//#include "SDL.h"
//#include "SDL_image.h"
//#include "oocdll.h"

//#include "i_surface.h"

// thank you to github user tronkko for making dirent.h for windows
// windows's file directory functions suck
// and literally every tutorial uses linux/posix/boost's DIR functions

/*
Error_t simgnode_start(SurfImageNode_t *head, SurfaceImage_t *img) {
    head = (SurfImageNode_t *) malloc(sizeof(SurfImageNode_t));
    if (head) {
        head->prev = NULLADDR;
        head->next = NULLADDR;
        head->simg = img;
    }
    else {
        return ERROR_MALLOC_NOSPACE;
    }
}

Error_t simgnode_append(SurfImageNode_t **head, SurfaceImage_t *img) {
    SurfImageNode_t *newnode = (SurfImageNode_t *) malloc(sizeof(SurfImageNode_t));

    if (newnode) {
        newnode->simg = img;
        newnode->next = NULL;

        if (*head) {
            SurfImageNode_t *tail = *head;

            while (tail->next) {
                tail = tail->next;
            }

            tail->next = newnode;
            newnode->prev = tail;
            return ERROR_NOERROR;
        }
        else {
            newnode->prev = NULL;
            *head = newnode;
            return ERROR_NOERROR;
        }
    }
    else {
        printf("cant append a new node to surface image node list, no mallloc space\n");
        return ERROR_MALLOC_NOSPACE;

    }
}

Error_t simgnode_addafter(SurfImageNode_t *prevnode, SurfaceImage_t *img) {
    if (prevnode) {
        SurfImageNode_t *newnode = (SurfImageNode_t *) malloc(sizeof(SurfImageNode_t));
        if (newnode) {
            if (prevnode->next) { // prevnode points to another node
                SurfImageNode_t *tmpnode = prevnode->next;
                newnode->simg = img;
                newnode->next = prevnode->next;
                prevnode->next = newnode;
                newnode->prev = prevnode;
                tmpnode->prev = newnode;
                return ERROR_NOERROR;
            }
            else { // prevnode is the end of the chain
                newnode->simg = img;
                newnode->next = NULLADDR;
                prevnode->next = newnode;
                newnode->prev = prevnode;
                return ERROR_NOERROR;
            }
        }
        else {
            printf("no malloc space to insert a new node\n");
            return ERROR_MALLOC_NOSPACE;
        }
    }
    else {
        printf("cant insert new node, previous node is null\n");
        return ERROR_ISNULLADDR;
    }
}


SurfaceImage_t ***simg_imginit(SurfaceImage_t **imgarray, int numimgs) {
    SurfaceImage_t *(*imgarrayptr)[];

    if (!imgarray) {
        Size_t tmpsize = numimgs * sizeof(SurfaceImage_t *);
        imgarray = (SurfaceImage_t **) malloc(tmpsize);

        if (imgarray) {
            for (int i = 0; i < numimgs; i++) {
                imgarray[i] = (SurfaceImage_t *) malloc(sizeof(SurfaceImage_t));
                if (imgarray[i]) {
                    memset(imgarray[i], 0, sizeof(SurfaceImage_t));
                }
                else {
                    printf("couldn't malloc space for imgarray[%d]\n", i);
                    simg_freedeep(&imgarray, numimgs);
                }
            }
        }
        else {
            printf("no malloc space for imgarray\n");
            return NULLADDR;
        }
    }
    else {
        printf("imgarray isnt null\n");
        return NULLADDR;
    }


    
    Size_t tmp = sizeof(SurfaceImage_t *) * numimgs;
    imgarray = (SurfaceImage_t **) malloc(tmp);
    if (imgarray) {
        for (int i = 0; i < numimgs; i++) {
            imgarray[i] = (SurfaceImage_t *) malloc(sizeof(SurfaceImage_t));
            if (imgarray[i]) {
                if (imgarray[i]->fpath) {
                    memset(imgarray[i], 0, sizeof(SurfaceImage_t));
                    str_new(imgarray[i]->fpath, "");

                }
                else {
                    printf("ran out of malloc space for fpath in images[%d]. freeing everything so far then returning null...\n", i);

                    for (int ohno = 0; ohno < i; ohno++) {
                        str_free(imgarray[ohno]->fpath);
                        free(imgarray[ohno]);
                    }
                    free(imgarray[i]);
                    return NULLADDR;
                }
            }
            else {
                printf("ran out of malloc space for images[%d]. freeing everything then returning null...\n", i);

                for (int uhoh = 0; uhoh < i; uhoh++) {
                    if (imgarray[uhoh]) {
                        str_free(imgarray[uhoh]->fpath);
                        free(imgarray[uhoh]);
                    }
                    return NULLADDR;
                }

            }
        }
        imgarrayptr = &imgarray;
        return imgarrayptr;
    }
    else {
        printf("no space for imgarray... returning null...\n");
        return NULLADDR;
    }
    

}

void simg_sortimgs(SurfaceImage_t *images, int numimgs) {
    if (numimgs <= 0) {
        if (images) {
            qsort(images, numimgs, sizeof(SurfaceImage_t), simg_imgcmp);
        }
        else {
            printf("image array is null... cant sort...\n");
        }
    }
    else {
        printf("invalid number of images! cant sort...\n");
    }
}

int simg_countimgs(const char *dpath) {
    DIR *d;
    struct dirent *dent;
    char *path;
    int numimgs = 0;

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

void simg_loadimgs(int curimg, const char *dir, SurfaceImage_t *imgarr) {
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
                        simg_loadimgs(curimg, path, imgarr);
                    }
                }
                else {
                    sprintf_s(path, tmpsize, "%s/%s", dir, dent->d_name);

                    imgarr[curimg].surf = IMG_Load(path);

                    if (imgarr[curimg].surf) {
                        imgarr[curimg].fpath = str_new(path);
                        SDL_SetSurfaceBlendMode(imgarr[curimg].surf, SDL_BLENDMODE_NONE);
                    }
                }
                free(path);

            }
            else {
                printf("no malloc space for simg_loadimg\n");
                closedir(d);
                return;
            }
        }
        closedir(d);
    }
}

int simg_imgcmp(const void *a, const void *b) {
    SurfaceImage_t *simga = (SurfaceImage_t *) a;
    SurfaceImage_t *simgb = (SurfaceImage_t *) b;

    return simgb->surf->h - simga->surf->h;
}

void simg_freedeep(SurfaceImage_t ***imgarrptr, int numimgs) {
    if (imgarrptr) {
        for (int i = 0; i < numimgs; i++) {
            if ((*imgarrptr)[i]) {
                if ((*imgarrptr)[i]->fpath) {
                    str_free((*imgarrptr)[i]->fpath);
                }
                if ((*imgarrptr)[i]->surf) {
                    SDL_FreeSurface((*imgarrptr)[i]->surf);
                }

                free((*imgarrptr)[i]);
            }
        }
        free(*imgarrptr);
    }
}
*/