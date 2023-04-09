#ifndef D_STRING_H
#define D_STRING_H

#include <stdlib.h>
#include <stdbool.h>

#include "d_common.h"

typedef char* String_t;
typedef size_t Strsize_t;

String_t str_new(const char *);

void str_append(String_t *, const char*);

void str_insert(String_t *, Strsize_t, const char *);

void str_replace(String_t *, Strsize_t, Strsize_t, const char *);

void str_remove(String_t, Strsize_t, Strsize_t);

void str_clear(String_t);

void str_free(String_t);

Strsize_t str_indexof(String_t, Strsize_t, const char *);

bool str_contains(String_t, const char *);

Strsize_t str_getlen(String_t);

Strsize_t str_getalloc(String_t);

void str_sanitize(String_t);

void str_tolower(String_t);

void str_toupper(String_t);

u8 str_equals(String_t, const char *);

#endif