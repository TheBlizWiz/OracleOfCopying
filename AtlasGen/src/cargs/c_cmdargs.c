#include <string.h>

#include "c_cmdargs.h"
#include "oocdll.h"


Cmdargs_t cmdargs_get(int argc, char *argv[]) {
    Cmdargs_t cargs;
    memset(&cargs, 0, sizeof(Cmdargs_t));

    cargs.aimgsize = DEFAULT_ATLAS_IMAGE_SIZE;
    cargs.padding = DEFAULT_ATLAS_PADDING;
    cargs.dirpath = str_new(ATLASGEN_DEFAULT_DIR_PATH);
    cargs.jsonpath = str_new(ATLASGEN_DEFAULT_JSON_PATH);
    cargs.atlaspath = str_new(ATLASGEN_DEFAULT_ATLAS_PATH);

    Error_t tmp = ERROR_NOERROR;
    for (int i = 0; i < argc; i++) {
        if (strncmp(argv[i], ATLASGEN_SIZE_ARGV, strlen(argv[i])) == 0) {
            cargs.aimgsize = atoi(argv[i + 1]);
        }
        if (strncmp(argv[i], ATLASGEN_PAD_ARGV, strlen(argv[i])) == 0) {
            cargs.padding = atoi(argv[i + 1]);
        }
        if (strncmp(argv[i], ATLASGEN_DIR_ARGV, strlen(argv[i])) == 0) {
            tmp = str_replace(&cargs.dirpath, 0, str_getlen(cargs.dirpath), argv[i + 1]);
            if (tmp != ERROR_NOERROR) {
                printf("str replace failed.... dammit... code: %lld\n", tmp);
            }
        }
        if (strncmp(argv[i], ATLASGEN_JSON_ARGV, strlen(argv[i])) == 0) {
            tmp = str_replace(&cargs.jsonpath, 0, str_getlen(cargs.jsonpath), argv[i + 1]);
            if (tmp != ERROR_NOERROR) {
                printf("str replace failed.... dammit... code: %lld\n", tmp);
            }
        }
        if (strncmp(argv[i], ATLASGEN_ATLAS_ARGV, strlen(argv[i])) == 0) {
            tmp = str_replace(&cargs.atlaspath, 0, str_getlen(cargs.atlaspath), argv[i + 1]);
            if (tmp != ERROR_NOERROR) {
                printf("str replace failed.... dammit... code: %lld\n", tmp);
            }
        }
        tmp = ERROR_NOERROR;
    }

    return cargs;
}

void cmdargs_free(Cmdargs_t cargs) {
    str_free(cargs.dirpath);
    str_free(cargs.jsonpath);
    str_free(cargs.atlaspath);
}
