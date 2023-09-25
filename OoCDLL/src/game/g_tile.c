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


Tile_t *tile_new(u32 tid, TileType_e tty, boolean c, Hitbox_t hb, u16 f, char *ttx, char *ftx) {
    Tile_t *t = (Tile_t *) malloc(sizeof(Tile_t));
    if (t) {
        t->tileid = tid;
        t->ttype = tty;
        t->collision = c;
        t->hbox = hb;
        t->flags = f;
        strncopy(t->tiletex, ttx, MAX_FNAME_LENGTH * sizeof(char));
        strncopy(t->floortex, ftx, MAX_FNAME_LENGTH * sizeof(char));
        return t;
    }
    else {
        errprintf("ERROR: no malloc space for new Tile_T *\n");
        return NULLADDR;
    }
}

Error_t tile_set(Tile_t *t, u32 tid, int tty, boolean col, u16 f, char *ftx, char *ttx) {
    if (t) {
        t->tileid = tid;
        t->ttype = tty;
        t->collision = col;
        t->flags = f;
        strncopy(t->tiletex, ttx, MAX_FNAME_LENGTH * sizeof(char));
        strncopy(t->floortex, ftx, MAX_FNAME_LENGTH * sizeof(char));
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

Error_t tile_drawfloor(Tile_t *tile, Hashmap_t **atlasmap, Coordinate c, App_t *app) {
    if (app) {
        if (tile) {
            if (atlasmap) {
                Image_t *ftx = atlas_getimage(atlasmap, tile->floortex);
                return (Error_t) SDL_BlitImage(app, ftx, c, 0, TF_NONE);
            }
            else {
                return (Error_t) ERROR_ISNULLADDR;
            }
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

Error_t tile_drawtile(Tile_t *tile, Hashmap_t **atlasmap, Coordinate c, App_t *app) {
    if (app) {
        if (tile) {
            if (atlasmap) {
                Image_t *ttx = atlas_getimage(atlasmap, tile->tiletex);
                return (Error_t) SDL_BlitImage(app, ttx, c, 0, TF_NONE);
            }
            else {
                return (Error_t) ERROR_ISNULLADDR;
            }
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

i32 tile_compare(const void *Tile_t_a, const void *Tile_t_b) {
    Tile_t *a = (Tile_t *) Tile_t_a;
    Tile_t *b = (Tile_t *) Tile_t_b;

    return b->tileid - a->tileid;
}

Error_t tile_load(const char *fpath, ListNode_t **tileset, Hashmap_t **atlasmap) {
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
    char *ttex;
    char *ftex;

    // TODO: replace with read from json file
    Hitbox_t hb = hbox_newdefault();

    if (atlasmap) {
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

                        ttex = cJSON_GetObjectItem(node, "tiletex")->valuestring;
                        ftex = cJSON_GetObjectItem(node, "floortex")->valuestring;

                        Tile_t *newtile = tile_new(tid, tty, col, hb, f, ttex, ftex);
                        *tileset = list_addtohead(*tileset, tid, newtile, tile_free, tile_compare);
                    }

                    cJSON_Delete(root);
                    free(jsontxt);
                    fclose(jsonf);
                    return (Error_t) ERROR_NOERROR;
                }
                else {
                    errprintf("ERROR: no malloc space for parsing json data\n");
                    fclose(jsonf);
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
        errprintf("ERROR: Hashmap_t *atlasmap is null, can't load textures for tiles\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}