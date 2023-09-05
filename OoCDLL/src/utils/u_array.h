#ifndef U_ARRAY_H
#define U_ARRAY_H

#include "defs/d_common.h"

#define GenArray(type) \
        { \
            struct GenericArray arrdata; \
            Size_t len; \
            type *arr; \
        }

#define Array_t(type) struct GenArray(type)

struct GenericArray {
    Size_t len;
    Size_t alloc;
    void *buf[];
};

#define array_new(arr) \
        

//array_new(Array_t *arr);
//array_add(Array_t *arr, Type *t);
//array_remove(Array_t *arr, Size_t index);
//array_sort(Array_t *arr, int (type_cmp_fnptr) (const Type *a, const Type *b));
//array_free(Array_t *arr, Error_t(type_free_fnptr) (Type *t));

#endif