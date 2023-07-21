#include <string.h>
#include <stdlib.h>

#include "defs/d_string.h"
#include "defs/d_utils.h"

#include "libs/cjson/cjson.h"

#include "r_image.h"

Error_t atlas_load(Hashmap_t *atlasmap, char *jsonfpath, SDL_Texture *atlasimg) {

    char *jsontxt = NULLADDR;
    Size_t n = 0;
    FILE *jsonf;
    cJSON *root;
    cJSON *node;
    char *filename;
    u32 x, y, w, h, r;

    if (atlasmap) {
        if (fopen_s(&jsonf, jsonfpath, "rb") == 0) {
            Error_t e = file_read(jsonf, &jsontxt, &n);
            
            if (e == ERROR_NOERROR && jsontxt) {
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

                        strncopy(img.fname, filename, MAX_FNAME_LENGTH);
                        img.isrotated = r;
                        img.tex = atlasimg;
                        img.rect = (SDL_Rect){ .x = x, .y = y, .w = w, .h = h };

                        hashmap_set(atlasmap, &img);
                    }
                    fclose(jsonf);
                    cJSON_Delete(root);
                    free(jsontxt);

                    return  (Error_t) ERROR_NOERROR;
                }
                else {
                    fclose(jsonf);
                    errprintf("ERROR: no malloc space for parsing json data\n");
                    return  (Error_t) ERROR_MALLOC_NOSPACE;
                }
            }
            else {
                fclose(jsonf);
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

Image_t *atlas_getimage(Hashmap_t *atlasmap, const char *filename) {
    Image_t *img;

    if (atlasmap) {

        Image_t tmp;
        zeroset(&tmp, sizeof(Image_t));
        strncopy(tmp.fname, filename, MAX_FNAME_LENGTH);
        img = (Image_t *) hashmap_delete(atlasmap, &tmp);


        if (img) {
            return img;
        }
        else {
            errprintf("ERROR: couldn't find %s in atlas hashmap\n", filename);
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: atlas hashmap is null\n");
        return NULLADDR;
    }
}