#include <string.h>
#include <stdlib.h>

#include "defs/d_string.h"
#include "defs/d_utils.h"

#include "libs/cjson/cjson.h"

#include "r_image.h"

Error_t atlas_load(Hashmap_t *atlasmap, char *jsonfpath, SDL_Texture *atlasimg) {

    String_t jsontxt = NULLADDR;
    FILE *jsonf;
    cJSON *root;
    cJSON *node;
    char *filename;
    u32 x, y, w, h, r;

    if (atlasmap) {
        if (fopen_s(&jsonf, jsonfpath, "rb") == 0) {

            Error_t e = file_read(jsonf, jsontxt);
            fclose(jsonf);
            if (e == ERROR_NOERROR) {
                root = cJSON_Parse(jsontxt);
                if (root) {
                    for (node = root->child; node != NULLADDR; node = node->next) {
                        filename = cJSON_GetObjectItem(node, "fpath")->valuestring;
                        x = cJSON_GetObjectItem(node, "x")->valueint;
                        y = cJSON_GetObjectItem(node, "y")->valueint;
                        w = cJSON_GetObjectItem(node, "w")->valueint;
                        h = cJSON_GetObjectItem(node, "h")->valueint;
                        r = cJSON_GetObjectItem(node, "isrotated")->valueint;

                        Image_t img;
                        zeroset(&img, sizeof(Image_t));

                        strncpy(img.fname, filename, MAX_FNAME_LENGTH);
                        img.fname[MAX_FNAME_LENGTH - 1] = '\0';
                        img.isrotated = r;
                        img.tex = atlasimg;
                        img.rect = (SDL_Rect){ .x = x, .y = y, .w = w, .h = h };

                        hashmap_set(atlasmap, &img);
                    }

                    cJSON_Delete(root);
                    str_free(jsontxt);

                    return  (Error_t) ERROR_NOERROR;
                }
                else {
                    errprintf("ERROR: no malloc space for parsing json data\n");
                    return  (Error_t) ERROR_MALLOC_NOSPACE;
                }
            }
            else {
                errprintf("ERROR: something went wrong reading json file\n");
                return e;
            }
        }
        else {
            errprintf("ERROR: couldn't open json file %s\n", jsonfpath);
            return (Error_t) ERROR_FILE_NOTFOUND;
        }
    }
    else {
        errprintf("ERROR: atlasmap is null, can't load into atlasmap\n");
        return (Error_t) ERROR_ISNULLADDR;
    }

}