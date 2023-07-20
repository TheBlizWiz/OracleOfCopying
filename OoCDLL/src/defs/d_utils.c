#include <stdio.h>
#include <string.h>

#include "d_string.h"
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

    if (*strptr == NULL) {
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

Error_t file_read(FILE *f, String_t outstr) {
    if (f == NULLADDR) {
        errprintf("ERROR: file is null\n");
        return (Error_t) ERROR_ISNULL_FILE;
    }

    if (outstr != NULLADDR) {
        errprintf("ERROR: output String_t is not null\n");
        return (Error_t) ERROR_ISNOTNULL_STRPTR;
    }

    fseek(f, 0, SEEK_END);
    Size_t len = ftell(f);
    fseek(f, 0, SEEK_SET);

    // i hate mallocing twice for the same data but i cant do anything about it
    char *tmp = (char *) malloc(len);
    if (tmp) {
        fread_s(tmp, len, sizeof(char), len, f);

        outstr = str_new(tmp);
        if (outstr) {
            free(tmp);
            return (Error_t) ERROR_NOERROR;
        }
        else {
            errprintf("ERROR: no malloc space for new String_t\n");
            free(tmp);
            return (Error_t) ERROR_MALLOC_NOSPACE;
        }
    }
    else {
        errprintf("ERROR: no malloc space for temporary char *\n");
        return (Error_t) ERROR_MALLOC_NOSPACE_READLINE;
    }
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