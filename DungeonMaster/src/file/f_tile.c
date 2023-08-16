#include "f_tile.h"

Error_t dg_writetile(cJSON *dgjsonfile, Tile_t *t, const char *tiletex, const char *floortex) {
    if (dgjsonfile && t) {
        cJSON *entry = cJSON_CreateObject();
        if (entry) {
            cJSON_AddNumberToObject(entry, "tileid", t->tileid);
            cJSON_AddNumberToObject(entry, "ttype", (int) t->ttype);
            cJSON_AddNumberToObject(entry, "collision", t->collision);

            // TODO: Add hitbox to json object in a way that doesnt
            // take 24 number entries

            cJSON_AddNumberToObject(entry, "flags", t->flags);

            // TODO: Rework these since Tile_ts use Image_t **
            // but the json file stores the file name
            // currently i just pass them in as parameters
            // but itd be nice if it just handled it for me

            cJSON_AddStringToObject(entry, "tiletex", tiletex);
            cJSON_AddStringToObject(entry, "floortex", floortex);

            cJSON_AddItemToArray(dgjsonfile, entry);
            return ERROR_NOERROR;
        }
        else {
            return ERROR_MALLOC_NOSPACE;
        }
    }
    else {
        return ERROR_ISNULLADDR;
    }
}