#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "d_string.h"
#include "d_macros.h"
#include "d_utils.h"

Error_t file_readline(String_t *strptr, FILE *f) {
    Size_t pos = 0;
    char c = 0;

    if (f == NULLADDR) {
        return (Error_t) ERROR_ISNULL_FILE;
    }

    if (strptr == NULLADDR) {
        return (Error_t) ERROR_ISNULL_STRPTR;
    }

    c = getc(f);
    if (c == EOF) {
        return (Error_t) ERROR_ISVALUE_EOF;
    }

    if (*strptr == NULLADDR) {
        String_t str = str_new(NULL);
        strptr = &str;
        if (strptr == NULLADDR) {
            return (Error_t) ERROR_MALLOC_NOSPACE_READLINE;
        }
    }

    while (c != EOF) {
        str_append(strptr, (char[2]) {
            c, '\0'
        });

        if (c == '\n' || c == '\r') {
            break;
        }

        c = getc(f);
    }

    return ERROR_NOERROR;
}

Error_t file_read(FILE *f, char **strptr, Size_t *szptr) {
    if (!f) {
        errprintf("ERROR: FILE *f is null\n");
        return ERROR_ISNULLADDR;
    }
    if (!strptr) {
        errprintf("ERROR: String_t *strptr is null\n");
        return ERROR_ISNULLADDR;
    }
    if (!szptr) {
        errprintf("ERROR: Size_t *szptr is null\n");
        return ERROR_ISNULLADDR;
    }

    Size_t sz = 0;
    Size_t used = 0;
    Size_t n;

    char *data = NULLADDR;
    char *tmp;

    if (ferror(f)) {
        errprintf("ERROR: file steam error... \nyeah idk i stole this off stackoverflow when my original code didnt work\n");
        return ERROR_GENERIC;
    }

    while (1) {
        if (used + FILE_BUFFER_SIZE + 1 > sz) {
            sz = used + FILE_BUFFER_SIZE + 1;

            if (sz <= used) {
                free(data);
                return ERROR_BUFFEROVERFLOW;
            }

            tmp = realloc(data, sz);
            if (!tmp) {
                errprintf("ERROR: no malloc space for realloc");
                free(data);
                return ERROR_REALLOC_NOSPACE;
            }
            data = tmp;
        }

        n = fread(data + used, sizeof(char), FILE_BUFFER_SIZE, f);
        if (n == 0)
            break;

        used += n;
    }

    if (ferror(f)) {
        errprintf("ERROR: file steam error\n");
        free(data);
        return ERROR_GENERIC;
    }

    tmp = realloc(data, used + 1);
    if (!tmp) {
        errprintf("ERROR: no malloc space for realloc");
        free(data);
        return ERROR_REALLOC_NOSPACE;
    }
    data = tmp;
    data[used] = '\0';

    *strptr = data;
    *szptr = used;

    return ERROR_NOERROR;
}

const char *file_getextension(const char *fname) {
    const char *dot = strrchr(fname, '.');
    if (!dot || dot == fname) {
        return "";
    }
    else {
        return dot + 1;
    }
}

u8 dbl_epsilon(double d, double exptval, double epsilon) {
    u8 b1 = (d <= (exptval + epsilon));
    u8 b2 = (d >= (exptval - epsilon));
    return b1 & b2;
}

int rng(int lo, int hi) {
    return (rand() % (hi - lo + 1)) + lo;
}

void *xalloc(void *ptr, Size_t nmemb, Size_t sz) {
    if ((nmemb >= MUL_NO_OVERFLOW || sz >= MUL_NO_OVERFLOW) &&
        nmemb > 0 && SIZE_MAX / nmemb < sz)
        return NULL;
    else
        return realloc(ptr, nmemb * sz);
}

int strcasecmp(const char *a, const char *b) {
    const unsigned char *pA = (const unsigned char *) a;
    const unsigned char *pB = (const unsigned char *) b;
    int result;

    if (pA == pB) {
        return 0;
    }

    while ((result = tolower(*pA) - tolower(*pB++)) == 0) {
        if (*pA++ == '\0') {
            break;
        }
    }

    return result;
}