#ifndef U_ARRAY_H
#define U_ARRAY_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "defs/d_common.h"

#define Array_t(T) \
    struct { \
        Size_t len; \
        Size_t cap; \
        T data[]; \
    }

#define array_start(arr, T) \
    _array_start_((arr), (sizeof(Size_t) + sizeof(Size_t) + sizeof((T))))

#define array_stop(arr, T, elem_free_fn) \
    _array_stop_((arr), elem_free_fn)



Error_t _array_start_(void *Array_t_arr, Size_t sz);
Error_t _array_stop_(void *Array_t_arr, free_fnptr);

#endif