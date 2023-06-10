#ifndef D_STRING_H
#define D_STRING_H

#ifdef DLL_EXPORT
#define D_STRING_API __declspec(dllexport)
#else
#define D_STRING_API __declspec(dllimport)
#endif

#include <stdlib.h>
#include <stdbool.h>

#include "oocdll.h"

D_STRING_API String_t str_new(const char *);

D_STRING_API void str_append(String_t *, const char *);

D_STRING_API void str_insert(String_t *, Size_t, const char *);

D_STRING_API void str_replace(String_t *, Size_t, Size_t, const char *);

D_STRING_API void str_remove(String_t, Size_t, Size_t);

D_STRING_API void str_clear(String_t);

D_STRING_API void str_free(String_t);

D_STRING_API Size_t str_indexof(String_t, Size_t, const char *);

D_STRING_API u8 str_contains(String_t, const char *);

D_STRING_API Size_t str_getlen(String_t);

D_STRING_API Size_t str_getalloc(String_t);

D_STRING_API void str_sanitize(String_t);

D_STRING_API void str_tolower(String_t);

D_STRING_API void str_toupper(String_t);

D_STRING_API u8 str_equals(String_t, const char *);

#endif