#include "u_array.h"
#include "defs/d_constants.h"
#include "defs/d_macros.h"

boolean _array_search_(GenArrayData_t *arr, Size_t *out, Size_t start, const void *tgtdata, cmp_fnptr cmp_fn) {
    if (arr) {
        if (out) {
            Size_t count = (start < arr->len) ? arr->len - start : 0;
            void *start_ptr = arraydata_getptr_offset(arr, start);
            void *ptr = bsearch(tgtdata, start_ptr, count, arr->sz, cmp_fn);

            if (!ptr) {
                return FALSE;
            }
            *out = (Size_t) ((uintptr_t) ptr - (uintptr_t) arraydata_getptr(arr));
            return TRUE;
        }
        else {
            errprintf("ERROR: Size_t *out is null\n");
            return FALSE;
        }
    }
    else {
        errprintf("ERROR: Array_t *arr is null\n");
        return FALSE;
    }
}