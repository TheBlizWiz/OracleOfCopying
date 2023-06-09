#include "a_json.h"

Error_t atlas_addjsonentry(cJSON *jsonfile, ListNode_t *simgnode) {
    if (simgnode && simgnode->data) {
        SurfaceImage_t *simg = (SurfaceImage_t *) simgnode->data;
        if (simg && simg->fpath) {
            if (jsonfile) {
                cJSON *entry = cJSON_CreateObject();
                if (entry) {
                    cJSON_AddStringToObject(jsonfile, "fpath", simg->fpath);
                    cJSON_AddNumberToObject(jsonfile, "x", simg->rect.x);
                    cJSON_AddNumberToObject(jsonfile, "y", simg->rect.y);
                    cJSON_AddNumberToObject(jsonfile, "w", simg->rect.w);
                    cJSON_AddNumberToObject(jsonfile, "h", simg->rect.h);
                    cJSON_AddNumberToObject(jsonfile, "isrotated", simg->isrotated);

                    cJSON_AddItemToArray(jsonfile, entry);

                    return (Error_t) ERROR_NOERROR;
                }
                else {
                    errprintf("ERROR: failed to make new cjson entry object\n");
                    return (Error_t) ERROR_MALLOC_NOSPACE;
                }
            }
            else {
                errprintf("ERROR: json file is null\n");
                return (Error_t) ERROR_ISNULLADDR;
            }
        }
        else {
            errprintf("ERROR: simg and/or simg->path are null after casting\n");
            return (Error_t) ERROR_ISNULLADDR;
        }
    }
    else {
        errprintf("ERROR: simgnode and/or simgnode->data are null\n");
        return (Error_t) ERROR_ISNULLADDR;
    }
}