#ifndef ary_H
#define ary_H

#ifdef OOCDLL_EXPORTS
#define ARRAY_H_API __declspec(dllexport)
#else
#define ARRAY_H_API __declspec(dllimport)
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define array_GROWTH_FACTOR 2.0

/* construct/destruct the element pointed to by `buf` */
ARRAY_H_API typedef void (*array_elemcb_t)(void *buf, void *userp);

/* the same as the `qsort` comparison function */
ARRAY_H_API typedef int (*array_cmpcb_t)(const void *a, const void *b);

/* return a malloc()ed string of `buf` in `ret` and its size, or -1 */
ARRAY_H_API typedef int (*array_joincb_t)(char **ret, const void *buf);

ARRAY_H_API typedef void *(*array_xalloc_t)(void *ptr, size_t nmemb, size_t size);
ARRAY_H_API typedef void (*array_xdealloc_t)(void *ptr);

/* struct size: 6x pointers + 4x size_t's + 1x type */
#define array(type)                                       \
	{                                               \
		struct arrayb s;                          \
		size_t len;    /* number of elements */ \
		type *buf;     /* array buffer */       \
		type *ptr;                              \
		type val;                               \
	}

#define Array_t(type) struct array(type)

struct arrayb {
	size_t len;
	size_t alloc;
	size_t sz;
	void *buf;
	array_elemcb_t ctor;
	array_elemcb_t dtor;
	void *userp;
};

/* `struct array a` is a void *-array */
struct array array(void *);
/* `struct array_xyz a` is a xyz-array... */
struct array_int array(int);
struct array_long array(long);
struct array_vlong array(long long);
struct array_size_t array(size_t);
struct array_double array(double);
struct array_char array(char);
struct array_charptr array(char *);

/* predefined callbacks */
ARRAY_H_API void array_cb_freevoidptr(void *buf, void *userp);
ARRAY_H_API void array_cb_freecharptr(void *buf, void *userp);

ARRAY_H_API int array_cb_cmpint(const void *a, const void *b);
ARRAY_H_API int array_cb_cmplong(const void *a, const void *b);
ARRAY_H_API int array_cb_cmpvlong(const void *a, const void *b);
ARRAY_H_API int array_cb_cmpsize_t(const void *a, const void *b);
ARRAY_H_API int array_cb_cmpdouble(const void *a, const void *b);
ARRAY_H_API int array_cb_cmpchar(const void *a, const void *b);
ARRAY_H_API int array_cb_strcmp(const void *a, const void *b);
ARRAY_H_API int array_cb_strcasecmp(const void *a, const void *b);

ARRAY_H_API int array_cb_voidptrtostr(char **ret, const void *elem);
ARRAY_H_API int array_cb_inttostr(char **ret, const void *elem);
ARRAY_H_API int array_cb_longtostr(char **ret, const void *elem);
ARRAY_H_API int array_cb_vlongtostr(char **ret, const void *elem);
ARRAY_H_API int array_cb_size_ttostr(char **ret, const void *elem);
ARRAY_H_API int array_cb_doubletostr(char **ret, const void *elem);
ARRAY_H_API int array_cb_chartostr(char **ret, const void *elem);

int strcasecmp(const char *a, const char *b);

/* forward declarations */
ARRAY_H_API void array_freebuf(struct arrayb *array);
ARRAY_H_API void *array_detach(struct arrayb *array, size_t *ret);
ARRAY_H_API int array_shrinktofit(struct arrayb *array);
ARRAY_H_API void *array_splicep(struct arrayb *array, size_t pos, size_t rlen, size_t alen);
ARRAY_H_API int array_index(struct arrayb *array, size_t *ret, size_t start, const void *data,
	array_cmpcb_t comp);
ARRAY_H_API int array_rindex(struct arrayb *array, size_t *ret, size_t start, const void *data,
	array_cmpcb_t comp);
ARRAY_H_API int array_reverse(struct arrayb *array);
ARRAY_H_API int array_join(struct arrayb *array, char **ret, const char *sep,
	array_joincb_t stringify);
ARRAY_H_API int array_swap(struct arrayb *array, size_t a, size_t b);
ARRAY_H_API int array_search(struct arrayb *array, size_t *ret, size_t start, const void *data,
	array_cmpcb_t comp);
ARRAY_H_API int array_unique(struct arrayb *array, array_cmpcb_t comp);

ARRAY_H_API extern array_xalloc_t array_xrealloc;

/**
 * array_use_as_realloc() - set a custom allocator function
 * @routine: replacement for realloc(ptr, nmemb, size)
 */
ARRAY_H_API void array_use_as_realloc(array_xalloc_t routine);

/**
 * array_use_as_free() - set a custom deallocator function
 * @routine: replacement for free(ptr)
 */
ARRAY_H_API void array_use_as_free(array_xdealloc_t routine);

/**
 * array_init() - initialize an array
 * @array: typed pointer to the array
 * @hint: count of elements to allocate memory for
 *
 * Return: When successful 1, otherwise 0 if array_grow() failed. Always returns
 *	1 if @hint is 0.
 *
 * Note!: Do not directly access elements that are not added to the array yet,
 *	only those with an index below @array->len.
 */
#define array_init(array, hint)                                 \
	((array)->s.alloc = (array)->s.len = (array)->len = 0,    \
	 (array)->s.sz = sizeof(*(array)->buf),                 \
	 (array)->s.ctor = (array)->s.dtor = NULL,              \
	 (array)->s.buf = (array)->s.userp = (array)->buf = NULL, \
	 array_grow((array), (hint)))

/**
 * array_release() - release an array
 * @array: typed pointer to the initialized array
 *
 * All elements are removed, the buffer is released and @array is reinitialized
 * with `array_init(@array, 0)`.
 */
#define array_release(array)                  \
	do {                              \
		array_freebuf(&(array)->s);   \
		(void)array_init((array), 0); \
	} while (0)

/**
 * array_setcbs() - set an array's constructor and destructor
 * @array: typed pointer to the initialized array
 * @_ctor: routine that creates new elements
 * @_dtor: routine that removes elements
 */
#define array_setcbs(array, _ctor, _dtor) \
	((array)->s.ctor = (_ctor), (array)->s.dtor = (_dtor), (void)0)

 /**
 * array_setuserp() - set an array's user-pointer for the ctor/dtor
 * @array: typed pointer to the initialized array
 * @ptr: pointer that gets passed to the callbacks
 */
#define array_setuserp(array, ptr) \
	((array)->s.userp = (ptr), (void)0)

/**
 * array_setinitval() - set an array's value used to initialize new elements
 * @array: typed pointer to the initialized array
 * @...: value that is used for new elements if @array->ctor() is NULL
 *
 * Note!: @... is like in array_push(). Also the init-value is left uninitialized
 *	when using array_init(). However, it has to be specified when
 *	initializing an array with array_INIT().
 */
#define array_setinitval(array, ...) \
	((array)->val = (__VA_ARGS__), (void)0)

/**
 * array_attach() - attach a buffer to an array
 * @array: typed pointer to the initialized array
 * @nbuf: pointer to a malloc()ed buffer
 * @nlen: number of elements pointed to by @nbuf
 * @nalloc: number of elements the buffer can hold
 *
 * The buffer @nbuf is henceforth owned by @array and cannot be relied upon
 * anymore and also must not be free()d directly.
 */
#define array_attach(array, nbuf, nlen, nalloc)       \
	do {                                      \
		array_freebuf(&(array)->s);           \
		(array)->s.buf = (array)->buf = nbuf; \
		(array)->s.len = (array)->len = nlen; \
		(array)->s.alloc = nalloc;          \
	} while (0)

/**
 * array_detach() - detach an array's buffer
 * @array: typed pointer to the initialized array
 * @size: pointer that receives @array's length, can be NULL
 *
 * A directly following array_release() is not needed.
 *
 * Return: The array buffer of @array. If @array's has no allocated memory, NULL is
 *	returned. You have to free() the buffer, when you no longer need it.
 */
#define array_detach(array, size)                                             \
	((array)->ptr = (array_detach)(&(array)->s, (size)), (array)->buf = NULL, \
	 (array)->len = 0, (array)->ptr)

/**
 * array_grow() - allocate new memory in an array
 * @array: typed pointer to the initialized array
 * @extra: count of extra elements
 *
 * Ensure that @array can hold at least @extra more elements.
 *
 * Return: When successful 1, otherwise 0 if realloc() failed.
 */
#define array_grow(array, extra) \
	((array_grow)(&(array)->s, (extra)) ? ((array)->buf = (array)->s.buf, 1) : 0)

/**
 * array_shrinktofit() - release unused allocated memory in an array
 * @array: typed pointer to the initialized array
 *
 * Return: When successful 1, otherwise 0 if realloc() failed. The array remains
 *	valid in either case.
 */
#define array_shrinktofit(array) \
	((array_shrinktofit)(&(array)->s) ? ((array)->buf = (array)->s.buf, 1) : 0)

/**
 * array_avail() - get the amount of unused memory in an array
 * @array: typed pointer to the initialized array
 *
 * Return: The number of elements that can be added without reallocation.
 */
#define array_avail(array) \
	((array)->s.alloc - (array)->s.len)

/**
 * array_setlen() - set an array's length
 * @array: typed pointer to the initialized array
 * @nlen: new number of elements @array holds
 *
 * If @nlen is above @array's current length, new elements are added, either by
 * calling @array->ctor() on them or by using the array's (possibly uninitialized)
 * init-value. Respectively, if @nlen is below @array's current length,
 * @array->dtor() is called on all elements above the new length.
 * However, the array is never reallocated and @nlen is truncated to not exceed
 * `@array.len + array_avail(@array)`.
 */
#define array_setlen(array, nlen)                                                  \
	do {                                                                   \
		size_t len = (nlen), i;                                        \
		if ((array)->s.len < len) {                                      \
			if ((array)->s.alloc < len)                              \
				len = (array)->s.alloc;                          \
			if ((array)->s.ctor) {                                   \
				for (i = (array)->s.len; i < len; i++)           \
					(array)->s.ctor(&(array)->buf[i],          \
					              (array)->s.userp);         \
			} else {                                               \
				for (i = (array)->s.len; i < len; i++)           \
					(array)->buf[i] = (array)->val;            \
			}                                                      \
		} else if ((array)->s.len > len && (array)->s.dtor) {              \
			for (i = len; i < (array)->s.len; i++)                   \
				(array)->s.dtor(&(array)->buf[i], (array)->s.userp); \
		}                                                              \
		(array)->s.len = (array)->len = len;                               \
	} while (0)

/**
 * array_clear() - empty an array
 * @array: typed pointer to the initialized array
 */
#define array_clear(array) \
	array_setlen((array), 0)

/**
 * array_push() - add a new element to the end of an array
 * @array: typed pointer to the initialized array
 * @...: value to push
 *
 * Return: When successful 1, otherwise 0 if array_grow() failed.
 *
 * Note!: @... is only a single value, it's denoted as varargs in order to cope
 *	with struct-literals, additionally, it is not evaluated if array_push()
 *	fails (so e.g. `strdup(s)` has no effect on failure).
 */
#define array_push(array, ...)                                                   \
	(((array)->s.len == (array)->s.alloc) ?                                  \
	 array_grow((array), 1) ?                                                \
	 ((array)->buf[(array)->len++, (array)->s.len++] = (__VA_ARGS__), 1) : 0 : \
	 ((array)->buf[(array)->len++, (array)->s.len++] = (__VA_ARGS__), 1))

/**
 * array_pushp() - add a new element slot to the end of an array (pointer)
 * @array: typed pointer to the initialized array
 *
 * Return: When successful a pointer to the new element slot, otherwise NULL if
 *	array_grow() failed.
 */
#define array_pushp(array)                                      \
	(((array)->s.len == (array)->s.alloc) ?                 \
	 array_grow((array), 1) ?                               \
	 &(array)->buf[(array)->len++, (array)->s.len++] : NULL : \
	 &(array)->buf[(array)->len++, (array)->s.len++])

/**
 * array_pop() - remove the last element of an array
 * @array: typed pointer to the initialized array
 * @ret: pointer that receives the popped element's value, can be NULL
 *
 * If @ret is NULL, @array->dtor() is called for the element to be popped.
 *
 * Return: When successful 1, otherwise 0 if there were no elements to pop.
 */
#define array_pop(array, ret)                                             \
	((array)->s.len ?                                               \
	 ((void *)(ret) != NULL) ?                                    \
	 (*(((void *)(ret) != NULL) ? (ret) : &(array)->val) =          \
	  (array)->buf[--(array)->s.len], (array)->len--, 1) :              \
	 (array)->s.dtor ?                                              \
	 ((array)->s.dtor(&(array)->buf[--(array)->s.len], (array)->s.userp), \
	  (array)->len--, 1) :                                          \
	 ((array)->s.len--, (array)->len--, 1) : 0)

/**
 * array_shift() - remove the first element of an array
 * @array: typed pointer to the initialized array
 * @ret: pointer that receives the shifted element's value, can be NULL
 *
 * If @ret is NULL, @array->dtor() is called for the element to be shifted.
 *
 * Return: When successful 1, otherwise 0 if there were no elements to shift.
 */
#define array_shift(array, ret)                                                 \
	((array)->s.len ?                                                     \
	 ((void *)(ret) != NULL) ?                                          \
	 (*(((void *)(ret) != NULL) ? (ret) : &(array)->val) = (array)->buf[0], \
	  memmove(&(array)->buf[0], &(array)->buf[1],                           \
	          --(array)->s.len * (array)->s.sz), (array)->len--, 1) :         \
	 (array)->s.dtor ?                                                    \
	 ((array)->s.dtor(&(array)->buf[0], (array)->s.userp),                    \
	  memmove(&(array)->buf[0], &(array)->buf[1],                           \
	          --(array)->s.len * (array)->s.sz), (array)->len--, 1) :         \
	 (memmove(&(array)->buf[0], &(array)->buf[1],                           \
	          --(array)->s.len * (array)->s.sz), (array)->len--, 1) : 0)

/**
 * array_unshift() - add a new element to the beginning of an array
 * @array: typed pointer to the initialized array
 * @...: value to unshift
 *
 * Return: When successful 1, otherwise 0 if array_grow() failed.
 *
 * Note!: @... is like in array_push().
 */
#define array_unshift(array, ...) \
	(array_unshiftp(array) ? (*(array)->ptr = (__VA_ARGS__), 1) : 0)

/**
 * array_unshiftp() - add a new element slot to the beginning of an array
 * @array: typed pointer to the initialized array
 *
 * Return: When successful a pointer to the new element slot, otherwise NULL if
 *	array_grow() failed.
 */
#define array_unshiftp(array) \
	array_splicep((array), 0, 0, 1)

/**
 * array_splice() - add/remove elements from an array
 * @array: typed pointer to the initialized array
 * @pos: index at which to add/remove
 * @rlen: number of elements to remove
 * @data: pointer to new elements
 * @dlen: number of new elements to add
 *
 * Return: When successful 1, otherwise 0 if there were new elements to add but
 *	array_grow() failed (the array remains unchanged in this case).
 */
#define array_splice(array, pos, rlen, data, dlen)                        \
	(array_splicep((array), (pos), (rlen), (dlen)) ?                  \
	 (memcpy((array)->ptr, (data) ? (void *)(data) : (void *)(array), \
	         (data) ? (dlen) * (array)->s.sz : 0), 1) : 0)

/**
 * array_splicep() - add element slots/remove elements from an array
 * @array: typed pointer to the initialized array
 * @pos: index at which to add/remove
 * @rlen: number of elements to remove
 * @alen: number of new element slots to add
 *
 * Return: When successful a pointer to the first new element slot (position of
 *	the last removed element), otherwise NULL if there were new elements
 *	slots to allocate but array_grow() failed (the array remains unchanged in
 *	this case).
 */
#define array_splicep(array, pos, rlen, alen)                                     \
	(((array)->ptr = (array_splicep)(&(array)->s, (pos), (rlen), (alen))) ?     \
	 ((array)->buf = (array)->s.buf, (array)->len = (array)->s.len, (array)->ptr) : \
	 NULL)

/**
 * array_index() - get the first occurrence of an element in an array
 * @array: typed pointer to the initialized array
 * @ret: pointer that receives the element's position, can be NULL
 * @start: position to start looking from
 * @data: pointer to the data to look for
 * @comp: comparison function, if NULL then memcmp() is used
 *
 * Return: When successful 1 and @ret is set to the position of the element
 *	found, otherwise 0 and @ret is uninitialized.
 */
#define array_index(array, ret, start, data, comp)                       \
	((array)->ptr = (data), (array_index)(&(array)->s, (ret), (start), \
	                                  (array)->ptr, (comp)))

/**
 * array_rindex() - get the last occurrence of an element in an array
 * @array: typed pointer to the initialized array
 * @ret: pointer that receives the element's position, can be NULL
 * @start: position to start looking from (backwards)
 * @data: pointer to the data to look for
 * @comp: comparison function, if NULL then memcmp() is used
 *
 * Return: When successful 1 and @ret is set to the position of the element
 *	found, otherwise 0 and @ret is uninitialized.
 */
#define array_rindex(array, ret, start, data, comp)                       \
	((array)->ptr = (data), (array_rindex)(&(array)->s, (ret), (start), \
	                                   (array)->ptr, (comp)))

/**
 * array_reverse() - reverse an array
 * @array: typed pointer to the initialized array
 *
 * Return: When successful 1, otherwise 0 if realloc() failed.
 */

#define array_reverse(array) \
	(array_reverse)(&(array)->s)

 /**
 * array_sort() - sort all elements in an array
 * @array: typed pointer to the initialized array
 * @comp: comparison function
 */
#define array_sort(array, comp) \
	qsort((array)->s.buf, (array)->s.len, (array)->s.sz, (comp))

/**
 * array_join() - join all elements of an array into a string
 * @array: typed pointer to the initialized array
 * @ret: pointer that receives a pointer to the new string
 * @sep: pointer to the null-terminated separator
 * @stringify: stringify function, if NULL then @array is assumed to be a char *-
 *	array
 *
 * Return: When successful length of @ret, otherwise -1 with `*@ret == NULL` if
 *	realloc() failed. You have to free() *@ret, when you no longer need it.
 */
#define array_join(array, ret, sep, stringify) \
	(array_join)(&(array)->s, (ret), (sep), (stringify))

/**
 * array_slice() - select a part of an array into a new one
 * @array: typed pointer to the initialized array
 * @ret: typed pointer to an unitialized array
 * @start: position where to start the selection
 * @end: position where to end the selection (excluding)
 *
 * @ret will contain a shallow copy of the selected elements and is always
 * initialized with `array_init(@ret, 0)`. @array's init-value is also copied.
 *
 * Return: When successful 1, otherwise 0 if array_grow() failed.
 */
#define array_slice(array, ret, start, end)                                   \
	((void)array_init((ret), 0),                                        \
	 array_splice((ret), 0, 0, &(array)->buf[(start)],                    \
	            ((start) < (array)->s.len) ? ((start) < (end)) ?        \
	                                       (end) - (start) : 0 : 0) ? \
	 ((ret)->val = (array)->val, 1) : 0)

/**
 * array_clone() - create a shallow copy of an array
 * @array: typed pointer to the initialized array
 * @ret: typed pointer to an unitialized array
 *
 * Same as `array_slice(&old, &new, 0, old.len)`.
 *
 * Return: When successful 1, otherwise 0 if array_grow() failed.
 */
#define array_clone(array, ret) \
	array_slice((array), (ret), 0, (array)->s.len)

/**
 * array_insert() - add a new element to an array at a given position
 * @array: typed pointer to the initialized array
 * @pos: position where to insert
 * @...: value to insert
 *
 * Return: When successful 1, otherwise 0 if array_grow() failed.
 *
 * Note!: @... is like in array_push().
 */
#define array_insert(array, pos, ...)              \
	((array_splicep((array), (pos), 0, 1)) ?   \
	 (*(array)->ptr = (__VA_ARGS__), 1) : 0)

/**
 * array_insertp() - add a new element slot to an array at a given position
 * @array: typed pointer to the initialized array
 * @pos: position where to insert
 *
 * Return: When successful a pointer to the new element slot, otherwise NULL if
 *	array_grow() failed.
 */
#define array_insertp(array, pos) \
	array_splicep((array), (pos), 0, 1)

/**
 * array_remove() - remove an element of an array
 * @array: typed pointer to the initialized array
 * @pos: position of the element to remove
 *
 * Return: Pointer to the element following the deleted element.
 */
#define array_remove(array, pos) \
	array_splicep((array), (pos), 1, 0)

/**
 * array_emplace() - create a new element in an array
 * @array: typed pointer to the initialized array
 * @pos: position where to create the element
 *
 * After allocating the new element, it is initialized by either calling
 * @array->ctor() on it or by using the array's (possibly uninitialized) init-
 * value.
 *
 * Return: When successful 1, otherwise 0 if array_grow() failed.
 */
#define array_emplace(array, pos)                                         \
	(array_insertp((array), (pos)) ?                                  \
	 ((array)->s.ctor ? (array)->s.ctor((array)->ptr, (array)->s.userp) : \
	                  (void)(*(array)->ptr = (array)->val), 1) : 0)

/**
 * array_snatch() - remove an element of an array without calling the destructor
 * @array: typed pointer to the initialized array
 * @pos: position of the element to remove
 * @ret: pointer that receives the removed element's value, can be NULL
 *
 * Return: When successful 1, otherwise 0 if there was no element to remove.
 */
#define array_snatch(array, pos, ret)                                         \
	((array)->s.len ?                                                   \
	 ((void *)(ret) != NULL) ?                                        \
	 ((array)->ptr = &(array)->buf[((pos) < (array)->s.len) ?               \
	                           (pos) : (array)->s.len - 1],             \
	  *(((void *)(ret) != NULL) ? (ret) : &(array)->val) = *(array)->ptr, \
	  memmove((array)->ptr, (array)->ptr + 1,                             \
	          &(array)->buf[--(array)->s.len] - (array)->ptr),              \
	  (array)->len--, 1) :                                              \
	 ((array)->ptr = &(array)->buf[((pos) < (array)->s.len) ?               \
	                           (pos) : (array)->s.len - 1],             \
	  memmove((array)->ptr, (array)->ptr + 1,                             \
	          &(array)->buf[--(array)->s.len] - (array)->ptr),              \
	  (array)->len--, 1) : 0)                                           \

/**
 * array_swap() - swap two elements in an array
 * @array: typed pointer to the initialized array
 * @a: position of the first element
 * @b: position of the second element
 *
 * Return: When successful 1, otherwise 0 if realloc() failed.
 */
#define array_swap(array, a, b) \
	(array_swap)(&(array)->s, (a), (b))

/**
 * array_search() - search a sorted array for an element
 * @array: typed pointer to the sorted array
 * @ret: pointer that receives the element's position, can be NULL
 * @start: position to start searching from
 * @data: pointer to the data to search for
 * @comp: comparison function
 *
 * Return: When successful 1 and @ret is set to the position of the element
 *	found, otherwise 0 and @ret is uninitialized.
 */
#define array_search(array, ret, start, data, comp)                       \
	((array)->ptr = (data), (array_search)(&(array)->s, (ret), (start), \
	                                   (array)->ptr, (comp)))

/**
 * array_unique() - remove duplicates in an array
 * @array: typed pointer to the array
 * @comp: comparison function
 *
 * Return: When successful 1, otherwise 0 if realloc() failed.
 */
#define array_unique(array, comp) \
	((array_unique)(&(array)->s, (comp)) ? ((array)->len = (array)->s.len, 1) : 0)

static inline int (array_grow)(struct arrayb *array, size_t extra) {
	const double factor = array_GROWTH_FACTOR;
	size_t alloc;
	void *buf;

	if (array->len + extra <= array->alloc)
		return 1;
	if (array->alloc * factor < array->len + extra)
		alloc = array->len + extra;
	else
		alloc = array->alloc * factor;
	buf = array_xrealloc(array->buf, alloc, array->sz);
	if (!buf)
		return 0;
	array->alloc = alloc;
	array->buf = buf;
	return 1;
}

#endif
