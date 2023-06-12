#ifndef D_UTILS_H
#define D_UTILS_H

#ifdef OOCDLL_EXPORTS
#define D_UTILS_API __declspec(dllexport)
#else
#define D_UTILS_API __declspec(dllimport)
#endif

#include <stdio.h>

#include "d_constants.h"
#include "d_common.h"

/**
 * Reads a line of text from a file and puts it into a String_t.
 * A line is a series of characters read until either newline char or 
 * carriage return char is read.
 * 
 * \param String_t *strptr - pointer to a String_t
 * \param FILE *f - pointer to the file to read from
 * 
 * \return Size_t - can be a couple different values:
 *                    1. length of string if no errors
 *                    2. ERROR_ISNULL_FILE if f is NULLADDR
 *                    3. ERROR_ISNULL_STRPTR if strptr is NULLADDR
 *                    4. ERROR_ISVALUE_EOF if *f is empty
 *                    5. ERROR_MEMORY_NOSPACE if strptr can't resize to fit new string read from f
 */
D_UTILS_API Size_t file_readline(String_t *, FILE *);

/**
 * Returns true if double d is equal to exptval + or - epsilon. Used to give a bit of tolerance for double values.
 * \param double d - input value
 * \param double exptval - expected value of d
 * \param double epsilon - tolerance of d versus exptval
 * \return bool - true if d falls within exptval + or - epsilon
 * 
 */
D_UTILS_API u8 dbl_epsilon(double, double, double);

/**
 * Randomly generate an integer between lo and hi inclusive.
 * Min value will be lo, max value will be hi.
 * 
 * \param int lo - minimum value that can be randomly generated
 * \param int hi - maximum value that can be randomly generated
 * \return int - random int value
 */
D_UTILS_API int rng(int, int);

#endif