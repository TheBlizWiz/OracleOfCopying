#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include "d_utils.h"
#include "d_string.h"
#include "d_constants.h"

Size_t file_readline(String_t *strptr, FILE *f) {
    Size_t pos = 0;
    char c = 0;

    if (f == NULLADDR) {
        return (Size_t) ERROR_ISNULL_FILE;
    }

    if (strptr == NULLADDR) {
        return (Size_t) ERROR_ISNULL_STRPTR;
    }

    c = _getc_nolock(f);
    if (c == EOF) {
        return(Size_t) ERROR_ISVALUE_EOF;
    }

    if (*strptr == NULL) {
        String_t str = str_new(NULL);
        strptr = &str;
        if (strptr == NULLADDR) {
            return (Size_t) ERROR_MEMORY_NOSPACE;
        }
    }

    while (c != EOF) {
        str_append(strptr, (char[2]) { c, '\0' });

        if (c == '\n' || c == '\r') {
            break;
        }

        c = _getc_nolock(f);
    }

    return str_getlen(*strptr);
}

bool dbl_epsilon(double d, double exptval, double epsilon) {
    bool b1 = (d <= (exptval + epsilon));
    bool b2 = (d >= (exptval - epsilon));
    return b1 && b2;
}

int rng(int lo, int hi) {
    return (rand() % (hi - lo + 1)) + lo;
}