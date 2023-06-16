#include <string.h>

#include "c_cmdargs.h"
#include "oocdll.h"

Cmdargs_t cmdargs_get(int argc, char *argv[]) {
    Cmdargs_t cargs;

    cargs.aimgsize = 1024;
    cargs.padding = 0;
    cargs.dirpath = str_new("E:/MSVC/source/repos/OracleOfCopying/OracleOfCopying/textures");

    for (int i = 0; i < argc; i++) {
        if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-size") == 0) {
            cargs.aimgsize = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "-pad") == 0 || strcmp(argv[i], "-padding") == 0) {
            cargs.padding = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-dir") == 0 || strcmp(argv[i], "-directory") == 0) {
                cargs.dirpath = str_replace(cargs.dirpath, 0, str_getlen(cargs.dirpath), argv[i + 1]);
        }
    }

    return cargs;
}