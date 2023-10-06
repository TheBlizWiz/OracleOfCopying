#include "u_array.h"
#include "defs/d_constants.h"

Error_t _array_start_(void *Array_t_arr, Size_t sz) {
    if (!Array_t_arr) {
        Array_t_arr = malloc(sz);
        if (Array_t_arr) {
            return (Error_t) ERROR_NOERROR;
        }
        else {
            return (Error_t) ERROR_MALLOC_NOSPACE;
        }
    }
    else {
        return (Error_t) ERROR_ISNOTNULLADDR;
    }
}

Error_t _array_stop_(void *Array_t_arr, free_fnptr elem_free) {
    return (Error_t) 0;
}