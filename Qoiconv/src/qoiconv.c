#include "qoiconv.h"
#include "dirent.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QOI_IMPLEMENTATION
#include "qoi.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#define STBI_NO_LINEAR
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#ifdef _DEBUG
#define errprintf printf
#endif

#ifdef NDEBUG
#define errprintf //
#endif


const char *getfileextension(const char *fname) {
    const char *dot = strrchr(fname, '.');
    if (!dot || dot == fname) {
        return "";
    }
    else {
        return dot + 1;
    }
}

void getpngfiles(const char *dirpath) {
    DIR *d;
    struct dirent *dent;
    char *path, *qoipath;


    if ((d = opendir(dirpath)) != NULL) {
        while ((dent = readdir(d)) != NULL) {
            size_t tmpsize = strlen(dirpath) + strlen(dent->d_name) + 2;
            path = (char *) malloc(tmpsize);
            if (path) {
                if (dent->d_type == DT_DIR) {
                    if (dent->d_name[0] != '.') {
                        sprintf_s(path, tmpsize, "%s\\%s", dirpath, dent->d_name);
                        getpngfiles(path);
                    }
                }
                else {
                    sprintf_s(path, tmpsize, "%s\\%s", dirpath, dent->d_name);

                    const char *ext = getfileextension(path);
                    if (strcmp(ext, "png") == 0) {
                        qoipath = _strdup(path);
                        if (qoipath) {
                            size_t tmpidx = strlen(qoipath);

                            qoipath[tmpidx - 3] = 'q'; // manually
                            qoipath[tmpidx - 2] = 'o'; // change
                            qoipath[tmpidx - 1] = 'i'; // file extension

                            qoiconv(path, qoipath);

                            free(qoipath);
                        }
                        else {
                            free(path);
                            closedir(d);
                            return;
                        }
                    }
                }
                free(path);

            }
            else {
                closedir(d);
                return;
            }
        }
        closedir(d);
    }
}

void qoiconv(const char *pngfpath, const char *qoifpath) {
    void *px = NULL;
    int w, h, channels;

    if (!stbi_info(pngfpath, &w, &h, &channels)) {
        errprintf("ERROR: Couldn't read png file %s\n", pngfpath);
        return;
    }

    if (channels != 3) {
        channels = 4;
    }

    px = (void *) stbi_load(pngfpath, &w, &h, NULL, channels);

    if (!px) {
        errprintf("ERROR: Couldn't load and decode %s\n", pngfpath);
    }

    int enc = qoi_write(qoifpath, px, &(qoi_desc){.width = w, .height = h, .channels = channels, .colorspace = QOI_SRGB});

    if (!enc) {
        errprintf("ERROR: Couldn't write/encode %s\n", qoifpath);
    }

    free(px);
}

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage:   qoiconv -directory <directory path>\n");
        printf("Example: qoiconv -directory \"E:\\MSVC\\textures\\\"");
        return 1;
    }

    if (strncmp(argv[1], "-directory", strlen(argv[1])) == 0) {
        getpngfiles(argv[2]);
    }
    else {
        printf("Invalid arguments\n");
        printf("Usage:   qoiconv -directory <directory path>\n");
        printf("Example: qoiconv -directory \"E:\\MSVC\\textures\\\"");
        return 2;
    }

    return 0;
}