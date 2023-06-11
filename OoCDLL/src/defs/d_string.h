#ifndef D_STRING_H
#define D_STRING_H

#ifdef OOCDLL_EXPORTS
#define D_STRING_API __declspec(dllexport)
#else
#define D_STRING_API __declspec(dllimport)
#endif

#include <stdlib.h>
#include <stdbool.h>

#include "defs/d_common.h"

/**
 * String on heap (malloc). Works just like a char * so use it just like that.
 * Holds length in chars and length in allocated bytes in the Strdata_t struct that its hiding.
 * Get the length of this string with str_getlen(String_t)
 * and get the allocated bytes with str_getalloc(String_t).
 */
typedef char *String_t;

/**
 * Struct to hold all the string data. You should never need to use any of this, it's all
 * accessible from the String_t.
 *
 * \param - Size_t alloc  - num of bytes allocated for the String_t. (i.e. length + 1)
 * \param - Size_t length - num of chars of how long this String_t is, not including null
 * \param - char[] buf    - the string char array (this is what String_t points to)
 */
typedef struct {
    Size_t alloc;
    Size_t length;
    char buf[];
} Strdata_t;

/**
 * Private method; do not use outside of d_string.c.
 * Makes new Strdata_t * with malloc with len bytes and returns it.
 *
 * \param  - Size_t len - num of bytes to allocate
 * \return - Strdata_t *sdat - pointer to Strdata_t, or NULLADDR if malloc fails
 */
D_STRING_API Strdata_t *str_alloc(Size_t);

/**
 * Private method; do not use outside of d_string.c.
 * Gets the Strdata_t * from a String_t *
 *
 * \param  - String_t s - the string to get the Strdata_t from
 * \return - Strdata_t *sdat - pointer to Strdata_t, or NULLADDR if s is null
 */
D_STRING_API Strdata_t *str_getdata(String_t);

/**
 * Create a new String_t on the heap from inputted const char *
 *
 * \param  - const char *carr - char* in "" to create new string out of
 * \return - String_t         - new String_t, or NULLADDR if any errors
 *
 */
D_STRING_API String_t str_new(const char *);

/**
 * Add const char *carr to the end of String_t *s.
 * If *s isn't long enough, realloc *s and then append *carr.
 *
 * \param  - String_t *s      - the string carr added onto the end of
 * \param  - const char *carr - the char arr that will be copied onto the end of *s
 * \return - Error_t          - ERROR_NOERROR if no errors, ERROR_ISNULLADDR if *s or *carr is null,
                                ERROR_REALLOC_NOSPACE if no memory space to realloc
 */
D_STRING_API Error_t str_append(String_t *, const char *);

/**
 * Inserts the entirety of *carr into String_t *s at index position pos
 * 
 * \param  - String_t *s      - String_t that gets edited
 * \param  - Size_t pos       - Index of first char of *s to append *carr
 * \param  - const char *carr - char arr to append
 * \return - Error_t          - ERROR_NOERROR if no errors,
                                ERROR_ISNULLADDR if *s or *carr is null,
                                ERROR_INDEX_OOB if pos is out of bounds,
                                ERROR_REALLOC_NOSPACE if no memory space to realloc
 *
 */
D_STRING_API Error_t str_insert(String_t *, Size_t, const char *);

/**
 * Replaces len number of chars from String_t *s starting at index pos with *carr
 * \param  - String_t *s      - String_t that gets edited
 * \param  - Size_t pos       - Index of first char where to replace with *carr
 * \param  - Size_t len       - Num of chars of *s to replace with *carr
 * \param  - const char *carr - char arr to append onto *s
 * \return - Error_t          - ERROR_NOERROR if no errors, 
                                ERROR_ISNULLADDR if *s or *carr is null,
                                ERROR_INDEX_OOB if pos is out of bounds, 
                                ERROR_LENGTH_INVALIDVALUE if len is too big or small, 
                                ERROR_REALLOC_NOSPACE if no memory space to realloc
 *
 */
D_STRING_API Error_t str_replace(String_t *, Size_t, Size_t, const char *);

/**
 * Removes len number of characters from String_t *s starting at index pos
 * \param  - String_t *s      - String_t that gets edited
 * \param  - Size_t pos       - Index of first char where to start removing chars
 * \param  - Size_t len       - Num of chars of *s to remove
 * \return - Error_t          - ERROR_NOERROR if no errors,
                                ERROR_ISNULLADDR if *s or *carr is null,
                                ERROR_INDEX_OOB if pos is out of bounds,
                                ERROR_LENGTH_INVALIDVALUE if len is too big or small,
 *
 */
D_STRING_API Error_t str_remove(String_t, Size_t, Size_t);

/**
 * Removes all characters from String_t *s except for the null char at the end
 * \param  - String_t s  - String_t that gets edited
 * \return - Error_t      - see str_remove()    
 */
D_STRING_API Error_t str_clear(String_t);

/**
 * Frees a String_t
 * \param  - String_t s - string to free
 * \return - None
 */
D_STRING_API void str_free(String_t);

/**
 * Returns the first index of src that has the entirety of *tgt in order starting at index position pos
 * \param  - String_t src    - String to look for *tgt in
 * \param  - Size_t pos      - First index of src to start looking for *tgt in
 * \param  - const char *tgt - char arr that is whats looked for in src
 * \return - Size_t -   0 if tgt is empty,
                       -1 if any errors or if tgt is not found in src, 
                       >0 if tgt is found in src, index of first char in src
 *                    
 *
 */
D_STRING_API Size_t str_indexof(String_t, Size_t, const char *);

/**
 * Checks if the entirety of *carr is within String_t *s
 * \param  - String_t src    - String to look for *tgt in
 * \param  - const char *tgt - char arr that is whats looked for in src
 * \return - 0 if s or tgt is null, 1 if src contains tgt, 0 if it does not
 */
D_STRING_API u8 str_contains(String_t, const char *);

/**
 * Gets the length in chars. Does not include null char at end.
 * \param - String_t s - string to get the length of
 * \return ERROR_ISNULL_STRPTR if s is null, length of s otherwise
 *
 */
D_STRING_API Size_t str_getlen(String_t);

/**
 * Gets the allocated length in bytes. (i.e. length + 1)
 * \param - String_t s - string to get the allocated bytes of
 * \return ERROR_ISNULL_STRPTR if s is null, allocated bytes of s otherwise
 *
 */
D_STRING_API Size_t str_getalloc(String_t);

/**
 * Removes all control characters except null from a String_t s
 *
 * \param  - String_t s - String to clean
 * \return - ERROR_ISNULLADDR if s is null, ERROR_NOERROR otherwise
 */
D_STRING_API Error_t str_sanitize(String_t);

/**
 * Changes a String_t s to make all letters lowercase
 *
 * \param  - String_t s - String_t to edit
 * \return - ERROR_ISNULLADDR if s is null, ERROR_NOERROR otherwise 
 */
D_STRING_API Error_t str_tolower(String_t);

/**
 * Changes a String_t s to make all letters uppercase
 *
 * \param  - String_t s - String_t to edit
 * \return - ERROR_ISNULLADDR if s is null, ERROR_NOERROR otherwise
 */
D_STRING_API Error_t str_toupper(String_t);

/**
 * Checks if String_t s is the same as const char *carr
 *
 * \param  - String_t s       - String_t to check
 * \param  - const char *carr - char arr that s needs to be equal to
 * \return - 0 if s or *carr is null, 1 if s equals *carr, 0 if it does not
 */
D_STRING_API u8 str_equals(String_t, const char *);

#endif