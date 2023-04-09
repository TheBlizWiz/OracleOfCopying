#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "d_utils.h"
#include "d_string.h"
#include "d_constants.h"

Strsize_t file_readline(String_t *strptr, FILE *f) {
    Strsize_t pos = 0;
    char c = 0;

    if(f == NULL) {
        return (Strsize_t) ERROR_ISNULL_FILE;
    }

    if(strptr == NULL) {
        return (Strsize_t) ERROR_ISNULL_STRPTR;
    }

    c = _getc_nolock(f);
    if(c == EOF) {
        return(Strsize_t) ERROR_ISVALUE_EOF;
    }

    if(*strptr == NULL) {
        String_t str = str_new(NULL);
        strptr = &str;
        if(strptr == NULL) {
            return (Strsize_t) ERROR_MEMORY_NOSPACE;
        }
    }

    while(c != EOF) {
        str_append(strptr, (char[2]) {c, '\0'});

        if(c == '\n' || c == '\r') {
            break;
        }

        c = _getc_nolock(f);
    }

    return str_getlen(*strptr);
}

