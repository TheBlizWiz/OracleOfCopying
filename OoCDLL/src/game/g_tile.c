#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "defs/d_constants.h"
#include "defs/d_macros.h"
#include "defs/d_utils.h"
#include "libs/cjson/cjson.h"
#include "game/g_tile.h"
#include "game/g_hitbox.h"
#include "render/r_sdl.h"


Tile_t *tile_new(u32 tid, TileType_e tty, boolean c, Hitbox_t hb, u16 f, Image_t *ttx, Image_t *ftx) {
    Tile_t *t = (Tile_t *) malloc(sizeof(Tile_t));
    if (t) {
        t->tileid = tid;
        t->ttype = tty;
        t->collision = c;
        t->hbox = hb;
        t->flags = f;
        t->tiletex = &ttx;
        t->floortex = &ftx;
        return t;
    }
    else {
        errprintf("ERROR: no malloc space for new Tile_T *\n");
        return NULLADDR;
    }
}

Error_t tile_set(Tile_t *tile, u32 tid, int tty, boolean col, u16 f, Image_t *ftx, Image_t *ttx) {
    if (tile) {
        tile->tileid = tid;
        tile->ttype = tty;
        tile->collision = col;
        tile->flags = f;
        tile->floortex = &ftx;
        tile->tiletex = &ttx;
        return (Error_t) ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Tile_t *tile is null, can't set\n");
        return ERROR_ISNULLADDR;
    }
}


Error_t tile_free(Tile_t *t) {
    if (t) {
        free(t);
        return (Error_t) ERROR_NOERROR;
    }
    else {
        return (Error_t) ERROR_ISNULLADDR;
    }
}

Error_t tile_drawfloor(Tile_t *tile, Coordinate c, App_t *app) {
    if (app) {
        if (tile) {
            return (Error_t) SDL_BlitImage(app, *(tile->floortex), c, 0, TF_NONE);
        }
        else {
            errprintf("ERROR: Tile_t *tile is null, can't draw Tile_t\n");
            return ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: App_t *app is null, can't draw Tile_t\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t tile_drawtile(Tile_t *tile, Coordinate c, App_t *app) {
    if (app) {
        if (tile) {
            return (Error_t) SDL_BlitImage(app, *(tile->tiletex), c, 0, TF_NONE);
        }
        else {
            errprintf("ERROR: Tile_t *tile is null, can't draw Tile_t\n");
            return ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: App_t *app is null, can't draw Tile_t\n");
        return ERROR_ISNULLADDR;
    }
}

int tile_compare(const void *Tile_t_a, const void *Tile_t_b) {
    Tile_t *a = (Tile_t *) Tile_t_a;
    Tile_t *b = (Tile_t *) Tile_t_b;

    return b->tileid - a->tileid;
}

Error_t tile_load(const char *fpath, Array_t(Tile_t) tileset, Hashmap_t *atlasmap) {
    char *jsontxt = NULLADDR;
    Size_t n = 0;
    FILE *jsonf;
    cJSON *root;
    cJSON *node;
    Error_t e;

    u32 tid;
    TileType_e tty;
    boolean col;
    u16 f;
    Image_t *ftex;
    Image_t *ttex;
    char *tmp;

    // TODO: replace with read from json file
    Hitbox_t hb = hbox_newdefault();

    if (atlasmap) {
        if (tileset) {
            if (fopen_s(&jsonf, fpath, "rb") == 0) {
                e = file_read(jsonf, &jsontxt, &n);

                if (e == ERROR_NOERROR) {
                    root = cJSON_Parse(jsontxt);
                    if (root) {
                        for (node = root->child; node != NULLADDR; node = node->next) {

                            tid = cJSON_GetObjectItem(node, "tileid")->valueint;
                            tty = cJSON_GetObjectItem(node, "ttype")->valueint;
                            col = cJSON_GetObjectItem(node, "collision")->valueint;
                            f = cJSON_GetObjectItem(node, "flags")->valueint;

                            // TODO: add Hitbox here

                            tmp = cJSON_GetObjectItem(node, "tiletex")->valuestring;
                            ttex = atlas_getimage(atlasmap, tmp);

                            tmp = cJSON_GetObjectItem(node, "floortex")->valuestring;
                            ftex = atlas_getimage(atlasmap, tmp);

                            Tile_t newtile = {
                                .tileid = tid,
                                .ttype = tty,
                                .collision = col,
                                .flags = f,
                                .hbox = hb,
                                .tiletex = &ttex,
                                .floortex = &ftex
                            };

                            // array_push(tileset, newtile);

                            do {
                                Size_t __CURRENT_CAP__ = ((tileset) ? (&((GenArrayData_t *) (tileset))[-1])->cap : (Size_t) 0); 
                                if (__CURRENT_CAP__ <= ((tileset) ? (&((GenArrayData_t *) (tileset))[-1])->len : (Size_t) 0)) {
                                    do {
                                        const Size_t __DESIRED_SIZE__ = (((__CURRENT_CAP__) ? ((__CURRENT_CAP__) << 1) : 1)) * sizeof(*((tileset))) + sizeof(GenArrayData_t); 
                                        if ((tileset)) {
                                            void *__PTR0__ = (&((GenArrayData_t *) ((tileset)))[-1]); void *__PTR1__ = realloc(__PTR0__, __DESIRED_SIZE__); 
                                            if (__PTR1__) {
                                                ((tileset)) = ((void *) &((GenArrayData_t *) (__PTR1__))[1]); 
                                                do {
                                                    if (((tileset))) {
                                                        (&((GenArrayData_t *) (((tileset))))[-1])->cap = ((((__CURRENT_CAP__) ? ((__CURRENT_CAP__) << 1) : 1)));
                                                    }
                                                } while (0);
                                            }
                                        }
                                        else {
                                            void *__PTR2__ = malloc(__DESIRED_SIZE__); 
                                            if (__PTR2__) {
                                                ((tileset)) = ((void *) &((GenArrayData_t *) (__PTR2__))[1]); 
                                                do {
                                                    if (((tileset))) {
                                                        (&((GenArrayData_t *) (((tileset))))[-1])->len = (0);
                                                    }
                                                } while (0);
                                                do {
                                                    if (((tileset))) {
                                                        (&((GenArrayData_t *) (((tileset))))[-1])->elem_free = (((void *) 0));
                                                    }
                                                } while (0);
                                                do {
                                                    if (((tileset))) {
                                                        (&((GenArrayData_t *) (((tileset))))[-1])->cap = ((((__CURRENT_CAP__) ? ((__CURRENT_CAP__) << 1) : 1)));
                                                    }
                                                } while (0);
                                            }
                                        }
                                    } while (0);
                                } 
                                (tileset)[((tileset) ? (&((GenArrayData_t *) (tileset))[-1])->len : (Size_t) 0)] = (newtile);
                                do {
                                    if ((tileset)) {
                                        (&((GenArrayData_t *) ((tileset)))[-1])->len = (((tileset) ? (&((GenArrayData_t *) (tileset))[-1])->len : (Size_t) 0) + 1);
                                    }
                                } while (0);
                            } while (0);

                        }
                        return (Error_t) ERROR_NOERROR;
                    }
                    else {
                        errprintf("ERROR: no malloc space for parsing json data\n");
                        return (Error_t) ERROR_MALLOC_NOSPACE;
                    }
                }
                else {
                    errprintf("ERROR: something went wrong reading json file %s\n", fpath);
                    return (Error_t) e;
                }
            }
            else {
                errprintf("ERROR: couldn't open json file %s\n", fpath);
                return (Error_t) ERROR_FILE_NOTFOUND;
            }
        }
        else {
            errprintf("ERROR: Array_t(Tile_t) *tileset is null, init array before using\n");
            return (Error_t) ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: Hashmap_t *atlasmap is null, can't load textures for tiles\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}