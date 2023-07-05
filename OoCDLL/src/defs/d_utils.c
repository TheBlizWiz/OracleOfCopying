#include <stdio.h>
#include <string.h>

#include "d_string.h"
#include "d_utils.h"

Size_t file_readline(String_t *strptr, FILE *f) {
    Size_t pos = 0;
    char c = 0;

    if (f == NULLADDR) {
        return (Size_t) ERROR_ISNULL_FILE;
    }

    if (strptr == NULLADDR) {
        return (Size_t) ERROR_ISNULL_STRPTR;
    }

    c = getc(f);
    if (c == EOF) {
        return(Size_t) ERROR_ISVALUE_EOF;
    }

    if (*strptr == NULL) {
        String_t str = str_new(NULL);
        strptr = &str;
        if (strptr == NULLADDR) {
            return (Size_t) ERROR_MALLOC_NOSPACE_READLINE;
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

    return str_getlen(*strptr);
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