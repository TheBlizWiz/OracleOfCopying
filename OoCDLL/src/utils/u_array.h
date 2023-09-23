#ifndef U_ARRAY_H
#define U_ARRAY_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "defs/d_common.h"

// this is adapted from GH repo
// https://github.com/eteran/c-vector
// thank you for the help

DLLINCLUDE typedef struct GenArrayData GenArrayData_t;

struct GenArrayData {
    // length of generic array, ie how many slots are filled
    Size_t len;

    // capacity of generic array, ie how many slots are allocated in memory
    Size_t cap;

    // sizeof individual element T
    Size_t sz;

    // function pointer to free function for elements
    free_fnptr elem_free;
};

#define Array_t(type) type *

#define array_getdata(arr) \
    (&((GenArrayData_t *)(arr))[-1])

#define arraydata_getptr(ptr) \
    ((void *)&((GenArrayData_t *)(ptr))[1])

#define arraydata_getptr_offset(ptr, offset) \
    ((void *)&((GenArrayData_t *)(ptr))[1 + offset])

#define array_getlength(arr) \
    ((arr) ? array_getdata(arr)->len : (Size_t) 0)

#define array_getcapacity(arr) \
    ((arr) ? array_getdata(arr)->cap : (Size_t) 0)

#define array_getsize(arr) \
    ((arr) ? array_getdata(arr)->sz : (Size_t) 0)

#define array_getfreefn(arr) \
    ((arr) ? array_getdata(arr)->elem_free : NULL)

#define array_setcapacity(arr, __CAPACITY__) \
    do { \
        if(arr) { \
            array_getdata(arr)->cap = (__CAPACITY__); \
        } \
    } while (0)

#define array_setlength(arr, __LENGTH__) \
    do { \
        if(arr) { \
            array_getdata(arr)->len = (__LENGTH__); \
        } \
    } while (0)

#define array_setsize(arr, __SIZE__) \
    do { \
        if(arr) { \
            array_getdata(arr)->sz = (__SIZE__); \
        } \
    } while (0)

#define array_setfreefn(arr, __ELEM_FREE__) \
    do { \
        if(arr) { \
            array_getdata(arr)->elem_free = (__ELEM_FREE__); \
        } \
    } while (0)

#define array_grow(arr, n) \
    do { \
        const Size_t __DESIRED_SIZE__ = (n) * sizeof(*(arr)) + sizeof(GenArrayData_t); \
        if(arr) { \
            void *__PTR0__ = array_getdata(arr); \
            void *__PTR1__ = realloc(__PTR0__, __DESIRED_SIZE__); \
            if(__PTR1__) { \
                (arr) = arraydata_getptr(__PTR1__); \
                array_setcapacity((arr), (n)); \
            } \
        } \
        else { \
            void *__PTR2__ = malloc(__DESIRED_SIZE__); \
            if(__PTR2__) { \
                (arr) = arraydata_getptr(__PTR2__); \
                array_setlength((arr), 0); \
                array_setfreefn((arr), NULL); \
                array_setcapacity((arr), (n)); \
                array_setsize((arr), sizeof(*(arr))); \
            } \
        } \
    } while (0)

#define array_isempty(arr) \
    (array_getlength(arr) == 0)

#define array_allocate(arr, n) \
    do { \
        Size_t __CURRENT_CAP__ = array_getcapacity(arr); \
        if(__CURRENT_CAP__ < (n)) { \
            array_grow((arr), (n)); \
        } \
    } while (0)

#define array_start(arr, c, e_free) \
    do { \
        if(!(arr)) { \
            array_allocate((arr), (c)); \
            array_setfreefn((arr), (e_free)); \
        } \
    } while (0)

#define array_delete(arr, idx) \
    do { \
        if((arr)) { \
            const Size_t __CURRENT_LEN__ = array_getlength((arr)); \
            if((idx) < __CURRENT_LEN__) { \
                free_fnptr __CURRENT_ELEM_FREE__ = array_getfreefn((arr)); \
                if(__CURRENT_ELEM_FREE__) { \
                    __CURRENT_ELEM_FREE__(&(arr)[idx]); \
                } \
                array_setlength((arr), __CURRENT_LEN__ - 1); \
                memmove((arr) + (idx), (arr) + (idx) + 1, sizeof(*(arr)) * (__CURRENT_LEN__) - 1 - (idx))); \
            } \
        } \
    while(0)

#define array_clear(arr) \
    do { \
        if((arr)) { \
            free_fnptr __CURRENT_ELEM_FREE__ = array_getfreefn((arr)); \
            if(__CURRENT_ELEM_FREE__) { \
                for(Size_t __I__ = 0; __I__ < array_getlength((arr)); ++__I__) { \
                    __CURRENT_ELEM_FREE__(&(arr)[__I__]); \
                } \
            } \
            array_setlength((arr), 0); \
        } \
    } while (0)

#define array_free(arr) \
    do { \
        if((arr)) { \
            void *__PTR0__ = array_getdata((arr)); \
            free_fnptr __CURRENT_ELEM_FREE__ = array_getfreefn((arr)); \
            if(__CURRENT_ELEM_FREE__) { \
                for(Size_t __I__ = 0; __I__ < array_getlength((arr)); ++__I__) { \
                    __CURRENT_ELEM_FREE__(&(arr)[__I__]); \
                } \
            } \
            free(__PTR0__); \
        } \
    } while (0)

#define array_getfirst(arr) \
    (arr)

#define array_getlast(arr) \
    ((arr) ? &((arr)[array_getlength(arr)]) : NULL )

#define array_getnextgrow(len) \
    ((len) ? ((len) << 1) : 1)

#define array_push(arr, T) \
    do { \
        Size_t __CURRENT_CAP__ = array_getcapacity(arr); \
        if(__CURRENT_CAP__ <= array_getlength(arr)) { \
            array_grow((arr), array_getnextgrow(__CURRENT_CAP__)); \
        } \
        (arr)[array_getlength(arr)] = (T); \
        array_setlength((arr), array_getlength(arr) + 1); \
    } while (0)

#define array_insert(arr, idx, T) \
    do { \
        Size_t __CURRENT_CAP__ = array_getcapacity(arr); \
        if(__CURRENT_CAP__ <= array_getlength(arr)) { \
            array_grow((arr), array_getnextgrow(__CURRENT_CAP__)); \
        } \
        if((idx) < array_getlength(arr)) { \
            memmove((arr) + (idx) + 1, (arr) + (idx), sizeof(*(arr)) * ((array_getlength(arr)) - (idx))); \
        } \
        (arr)[(idx)] = (T); \
        array_setlength((arr), array_getlength(arr) + 1); \
    } while (0)

#define array_pop(arr) \
    do { \
        free_fnptr __CURRENT_ELEM_FREE__ = array_getfreefn((arr)); \
        if(__CURRENT_ELEM_FREE__) { \
            __CURRENT_ELEM_FREE__(&(arr)[array_getlength(arr) - 1]); \
        } \
        array_setlength((arr), array_getlength(arr) + 1); \
    } while (0)

#define array_copy(from, to) \
    do { \
        if((from)) { \
            array_grow(to, array_getlength(from)); \
            array_setlength(to, array_getlength(from)); \
            memcpy((to), (from), array_getlength(from) * sizeof(*(from))); \
        } \
    } while (0)

#define array_iterate(arr, T_ptr_itr) \
    for(T_ptr_itr = array_getfirst(arr); T_ptr_itr < array_getlast(arr); T_ptr_itr++)


#define array_search(arr, out, startidx, tgtdata, cmpfunc) \
    _array_search_(array_getdata(arr), out, startidx, tgtdata, cmpfunc); \

#define array_foreach(arr, func) \
    do { \
        if((arr) && (func)) { \
            for(Size_t __I__ = 0; __I__ < array_getlength(arr); __I__++) { \
                func((arr)[__I__]); \
            } \
        } \
    } while (0)

#define array_stop(arr, ...) \
    do { \
        if(arr) { \
            if(array_getdata(arr)->elem_free) { \
                array_free(arr); \
            } \
            else { \
                free_fnptr __VARARGS_ELEM_FREE__ = (__VA_ARGS__); \
                if(__VARARGS_ELEM_FREE__) { \
                    array_foreach(&(arr), (__VARARGS_ELEM_FREE__)); \
                } \
                void *__PTR0__ = array_getdata((arr)); \
                free(__PTR0__); \
            } \
        } \
    } while (0)

DLLINCLUDE boolean _array_search_(GenArrayData_t * arr, Size_t * out, Size_t start, const void *tgtdata, cmp_fnptr cmp_fn);

#endif