#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "d_string.h"
#include "d_constants.h"

typedef struct strdata Strdata_t;

struct strdata {
    Strsize_t alloc;
    Strsize_t length;
    char buf[];
};

Strdata_t *str_alloc(Strsize_t length) {
    Strdata_t *sdat = malloc(sizeof(Strdata_t) + length + NULL_CHAR_SIZE);
    sdat->alloc = length+1;
    sdat->length = length;
    return sdat;
}

Strdata_t *str_getdata(String_t s) {
    return (Strdata_t *)&s[-sizeof(Strdata_t)];
}

String_t str_new(const char *carr) {
    Strdata_t *sdat = NULL;

    if (carr != NULL) {
        Strsize_t carrlen = strlen(carr);
        sdat = str_alloc(carrlen);
        memcpy(&sdat->buf, carr, carrlen);
        sdat->buf[carrlen] = '\0';
    } else {
        sdat = str_alloc(0);
        sdat->buf[0] = '\0';
    }

    return sdat->buf;
}

void str_append(String_t *s, const char *carr) {
    Strdata_t *sdat = str_getdata(*s);

    Strsize_t carrlen = strlen(carr);

    Strsize_t newlen = sdat->length + carrlen;

    if (sdat->alloc <= newlen + NULL_CHAR_SIZE) {
        sdat = realloc(sdat, sizeof(Strdata_t) + newlen);
        sdat->alloc = newlen + NULL_CHAR_SIZE;
    }

    memcpy(&sdat->buf[sdat->length], carr, carrlen);

    sdat->length = newlen;

    sdat->buf[newlen] = '\0';

    *s = sdat->buf;
}

void str_insert(String_t *s, Strsize_t pos, const char *carr) {
    Strdata_t *sdat = str_getdata(*s);

    Strsize_t carrlen = strlen(carr);

    Strsize_t newlen = sdat->length + carrlen;

    if (sdat->alloc <= newlen + NULL_CHAR_SIZE) {
        Strdata_t *new_sdat = str_alloc(newlen);

        memcpy(new_sdat->buf, sdat->buf, pos);
        memcpy(&new_sdat->buf[pos+carrlen], &sdat->buf[pos], sdat->length-pos);

        free(sdat);
        sdat = new_sdat;

    } else {
        memmove(&sdat->buf[pos], &sdat->buf[pos+carrlen], sdat->length - pos);
    }

    sdat->length = newlen;

    memcpy(&sdat->buf[pos], carr, carrlen);

    sdat->buf[newlen] = '\0';

    *s = sdat->buf;
}

void str_replace(String_t* s, Strsize_t pos, Strsize_t len, const char *carr) {
    Strdata_t *sdat = str_getdata(*s);

    Strsize_t carrlen = strlen(carr);

    Strsize_t newlen = sdat->length + carrlen - len;

    if (sdat->alloc <= newlen + NULL_CHAR_SIZE) {
        Strdata_t *new_sdat = str_alloc(newlen);

        memcpy(new_sdat->buf, sdat->buf, pos);
        memcpy(&new_sdat->buf[pos+carrlen], &sdat->buf[pos+len], sdat->length-pos-len);

        free(sdat);

        sdat = new_sdat;

    } else {
        memmove(&sdat->buf[pos+carrlen], &sdat->buf[pos+len], sdat->length-pos-len);
    }

    sdat->length = newlen;

    memcpy(&sdat->buf[pos], carr, carrlen);

    sdat->buf[newlen] = '\0';

    *s = sdat->buf;
}

void str_remove(String_t s, Strsize_t pos, Strsize_t len) {
    Strdata_t *sdat = str_getdata(s);
    // anyone who puts in a bad index can face the consequences on their own
    memmove(&sdat->buf[pos], &sdat->buf[pos+len], sdat->length - pos);
    sdat->length -= len;
    sdat->buf[sdat->length] = '\0';
}

void str_clear (String_t s) {
    str_remove(s, 0, str_getlen(s));
};

void str_free(String_t s) {
    free(str_getdata(s));
}

Strsize_t str_getlen(String_t s) {
    return ((Strsize_t *)s)[INDEX_STR_LEN];
}

Strsize_t str_getalloc(String_t s) {
    return ((Strsize_t *)s)[INDEX_STR_ALLOC];
}

Strsize_t str_indexof(String_t src, Strsize_t pos, const char *tgt) {
    Strsize_t tgtlen = strlen(tgt);
    Strsize_t srclen = str_getlen(src);

    if(srclen <= 0 || tgtlen < 0 || tgtlen > srclen || pos > srclen || pos < 0) {
        return (Strsize_t) -1;
    }

    if(tgtlen == 0) {
        return srclen;
    }

    Strsize_t srcidx = pos;
    Strsize_t tgtidx = 0;

    // search for first instance of tgt[0] in src starting at pos
    for(srcidx = pos; srcidx < srclen; srcidx++) {
         // src[srcidx] == tgt[0]
        if(src[srcidx] == tgt[tgtidx]) {
            // continue to see if src[srcidx + 1] == tgt[1] and so on until tgt[tgtlen - 1]
            if(tgtlen == 1) {
                return srcidx;
            }
            else {
                tgtidx++;
            }

            for(Strsize_t srcidx2 = srcidx + 1; srcidx2 < srclen && tgtidx < tgtlen; srcidx2++) {
                if((src[srcidx2] == tgt[tgtidx]) && (tgtidx + 1 == tgtlen)) {
                    return srcidx;
                }
                else if((src[srcidx2] == tgt[tgtidx]) && (tgtidx + 1 != tgtlen))  {
                    tgtidx++;
                }
                else {
                    tgtidx = 0;
                    break;
                }
            }
        }
    }
    return (Strsize_t) -1; // tgt doesn't exist in src
}

bool str_contains(String_t src, const char *tgt) {
    return str_indexof(src, 0, tgt) >= 0;
}

void str_sanitize(String_t s) {
    Strsize_t slen = str_getlen(s);
    if(slen == 0) {
        return;
    }

    for(Strsize_t i = 0; i < slen; i++) {
        if(iscntrl((int) s[i]) && s[i] != '\0') {
            str_remove(s, i, 1);
            i--;
            slen = str_getlen(s);
        }
    }
}

void str_tolower(String_t s) {
    for(Strsize_t i = 0; i < str_getlen(s); i++) {
        s[i] = tolower(s[i]);
    }
}

void str_toupper(String_t s) {
    for(Strsize_t i = 0; i < str_getlen(s); i++) {
        s[i] = toupper(s[i]);
    }
}

u8 str_equals(String_t s, const char *c) {
    if(strcmp(s, c) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}