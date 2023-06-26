#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "d_common.h"
#include "d_constants.h"
#include "d_string.h"

Strdata_t *str_alloc(Size_t len) {
    Strdata_t *sdat = malloc(sizeof(Strdata_t) + len + NULL_CHAR_SIZE);
    if (sdat) {
        sdat->alloc = len + 1;
        sdat->length = len;
        return sdat;
    }
    else
        return NULLADDR;
}

Strdata_t *str_getdata(String_t s) {
    if (!s)
        return NULLADDR;
    else
        return (Strdata_t *) &s[0 - sizeof(Strdata_t)];
}

String_t str_new(const char *carr) {
    Strdata_t *sdat = NULLADDR;

    if (carr) {
        Size_t carrlen = strlen(carr);
        sdat = str_alloc(carrlen);

        if (sdat) {
            memcpy(&sdat->buf, carr, carrlen);
            sdat->buf[carrlen] = '\0';
        }
        else
            return NULLADDR;
    }
    else {
        sdat = str_alloc(0);
        if (sdat)
            sdat->buf[0] = '\0';
        else
            return NULLADDR;
    }

    return sdat->buf;
}

String_t str_newfromlen(Size_t len) {
    Strdata_t *sdat = str_alloc(len + NULL_CHAR_SIZE);

    if (sdat) {
        for (Size_t i = 0; i <= len; i++) {
            sdat->buf[i] = 'A';
        }
        sdat->buf[len] = '\0';
        return sdat->buf;
    }
    else {
        return NULLADDR;
    }

}

Error_t str_append(String_t *s, const char *carr) {
    if (!s || !carr)
        return ERROR_ISNULLADDR;

    Strdata_t *sdat = str_getdata(*s);

    Size_t carrlen = strlen(carr);

    Size_t newlen = sdat->length + carrlen;

    if (sdat->alloc <= newlen + NULL_CHAR_SIZE && sdat->alloc != 0) {
        Strdata_t *sdat_tmp = (Strdata_t *) realloc(sdat, sizeof(Strdata_t) + newlen);
        if (!sdat_tmp) {
            return ERROR_REALLOC_NOSPACE;
        }
        else {
            sdat = sdat_tmp;
            sdat->alloc = newlen + NULL_CHAR_SIZE;
            memcpy(&sdat->buf[sdat->length], carr, carrlen);
            sdat->length = newlen;
            sdat->buf[newlen] = '\0';
            *s = sdat->buf;
        }
    }
    return ERROR_NOERROR;
}

Error_t str_insert(String_t *s, Size_t pos, const char *carr) {
    if (!s || !carr)
        return ERROR_ISNULLADDR;

    Strdata_t *sdat = str_getdata(*s);

    if (pos > sdat->length || pos < 0)
        return ERROR_INDEX_OOB;

    Size_t carrlen = strlen(carr);

    Size_t newlen = sdat->length + carrlen;

    if (sdat->alloc <= newlen + NULL_CHAR_SIZE && sdat->alloc != 0) {
        Strdata_t *new_sdat = str_alloc(newlen);
        if (new_sdat) {
            memcpy(new_sdat->buf, sdat->buf, pos);
            memcpy(&new_sdat->buf[pos + carrlen], &sdat->buf[pos], sdat->length - pos);

            free(sdat);
            sdat = new_sdat;
        }
        else {
            return ERROR_MALLOC_NOSPACE;
        }

    }
    else {
        memmove(&sdat->buf[pos], &sdat->buf[pos + carrlen], sdat->length - pos);
    }

    sdat->length = newlen;

    memcpy(&sdat->buf[pos], carr, carrlen);

    sdat->buf[newlen] = '\0';

    *s = sdat->buf;
    return ERROR_NOERROR;
}

Error_t str_replace(String_t *s, Size_t pos, Size_t len, const char *carr) {
    if (!s || !carr)
        return ERROR_ISNULLADDR;

    Strdata_t *sdat = str_getdata(*s);

    if (pos < 0 || pos > sdat->length)
        return ERROR_INDEX_OOB;
    if (len < 0 || len > sdat->length)
        return ERROR_LENGTH_INVALIDVALUE;


    Size_t carrlen = strlen(carr);

    Size_t newlen = sdat->length + carrlen - len;

    if (sdat->alloc <= newlen + NULL_CHAR_SIZE && sdat->alloc != 0) {
        Strdata_t *new_sdat = str_alloc(newlen);
        if (new_sdat) {

            memcpy(new_sdat->buf, sdat->buf, pos);
            memcpy(&new_sdat->buf[pos + carrlen], &sdat->buf[pos + len], sdat->length - pos - len);

            free(sdat);

            sdat = new_sdat;
        }
        else
            return ERROR_REALLOC_NOSPACE;
    }
    else {
        memmove(&sdat->buf[pos + carrlen], &sdat->buf[pos + len], sdat->length - pos - len);
    }

    sdat->length = newlen;

    memcpy(&sdat->buf[pos], carr, carrlen);

    sdat->buf[newlen] = '\0';

    *s = sdat->buf;

    return ERROR_NOERROR;
}

Error_t str_remove(String_t s, Size_t pos, Size_t len) {
    if (!s)
        return ERROR_ISNULLADDR;

    Strdata_t *sdat = str_getdata(s);

    if (pos <= 0 || pos > sdat->length)
        return ERROR_INDEX_OOB;
    if (len <= 0 || len > sdat->length)
        return ERROR_LENGTH_INVALIDVALUE;

    memmove(&sdat->buf[pos], &sdat->buf[pos + len], sdat->length - pos);
    sdat->length -= len;
    sdat->buf[sdat->length] = '\0';

    return ERROR_NOERROR;
}

Error_t str_clear(String_t s) {
    return str_remove(s, 0, str_getlen(s));
};

Error_t str_free(String_t s) {
    if (s) {
        free(str_getdata(s));
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: string is null, can't free\n");
        return ERROR_ISNULLADDR;
    }
}

Size_t str_indexof(String_t src, Size_t pos, const char *tgt) {
    Size_t tgtlen = strlen(tgt);
    Size_t srclen = str_getlen(src);

    if (srclen <= 0 || tgtlen < 0 || tgtlen > srclen || pos > srclen || pos < 0)
        return (Size_t) -1;

    if (tgtlen == 0)
        return srclen;

    Size_t srcidx = pos;
    Size_t tgtidx = 0;

    // search for first instance of tgt[0] in src starting at pos
    for (srcidx = pos; srcidx < srclen; srcidx++) {
        // src[srcidx] == tgt[0]
        if (src[srcidx] == tgt[tgtidx]) {
            // continue to see if src[srcidx + 1] == tgt[1] and so on until tgt[tgtlen - 1]
            if (tgtlen == 1) {
                return srcidx;
            }
            else {
                tgtidx++;
            }

            for (Size_t srcidx2 = srcidx + 1; srcidx2 < srclen && tgtidx < tgtlen; srcidx2++) {
                if ((src[srcidx2] == tgt[tgtidx]) && (tgtidx + 1 == tgtlen)) {
                    return srcidx;
                }
                else if ((src[srcidx2] == tgt[tgtidx]) && (tgtidx + 1 != tgtlen)) {
                    tgtidx++;
                }
                else {
                    tgtidx = 0;
                    break;
                }
            }
        }
    }
    return (Size_t) -1; // tgt doesn't exist in src
}

u8 str_contains(String_t src, const char *tgt) {
    if (!src || !tgt) {
        return 0;
    }
    else {
        return (str_indexof(src, 0, tgt) >= 0) ? 1 : 0;
    }
}

i32 str_contains_fptr(const void *string_t_src, const void *const_char_tgt) {
    if (!string_t_src || !const_char_tgt) {
        return 0;
    }
    else {
        return (str_indexof((String_t) string_t_src, 0, (const char *) const_char_tgt) >= 0) ? 1 : 0;
    }
}

i32 str_cmp_fptr(const void *string_t_src, const void *string_t_tgt) {
    String_t strsrc = (String_t) string_t_src;
    String_t strtgt = (String_t) string_t_tgt;
    return (i32) strcmp((const char *) strsrc, (const char *) strtgt);
}

Size_t str_getlen(String_t s) {
    if (!s)
        return ERROR_ISNULL_STRPTR;
    else
        return ((Size_t *) s)[INDEX_STR_LEN];
}

Size_t str_getalloc(String_t s) {
    if (!s)
        return ERROR_ISNULL_STRPTR;
    else
        return ((Size_t *) s)[INDEX_STR_ALLOC];
}

Error_t str_sanitize(String_t s) {
    if (!s)
        return ERROR_ISNULLADDR;

    Size_t slen = str_getlen(s);
    if (slen == 0) {
        return ERROR_NOERROR;
    }

    for (Size_t i = 0; i < slen; i++) {
        if (iscntrl((int) s[i]) && s[i] != '\0') { // TODO: can we remove null chars safely?
            str_remove(s, i, 1);
            i--;
            slen = str_getlen(s);
        }
    }

    return ERROR_NOERROR;
}

Error_t str_tolower(String_t s) {
    if (!s)
        return ERROR_ISNULLADDR;

    for (Size_t i = 0; i < str_getlen(s); i++) {
        s[i] = tolower(s[i]);
    }

    return ERROR_NOERROR;
}

Error_t str_toupper(String_t s) {
    if (!s)
        return ERROR_ISNULLADDR;

    for (Size_t i = 0; i < str_getlen(s); i++) {
        s[i] = toupper(s[i]);
    }

    return ERROR_NOERROR;
}

u8 str_equals(String_t s, const char *carr) {
    if (!s || !carr)
        return 0;
    else 
        return (strcmp(s, carr) == 0) ? 1 : 0;
}