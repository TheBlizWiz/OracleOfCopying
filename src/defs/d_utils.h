#ifndef D_UTILS_H
#define D_UTILS_H

#include <stdio.h>
#include <stdbool.h>
#include "d_string.h"
#include "d_common.h"

Size_t file_readline(String_t *, FILE *);

bool dbl_epsilon(double, double, double);

#endif