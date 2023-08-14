#ifndef M_MATH_H
#define M_MATH_H

#include "defs/d_common.h"

// sqrt(x^2 + y^2 + z^2) 
DLLINCLUDE const double hypot3(const double x, const double y, const double z);

// ax^2 + bx + c
DLLINCLUDE const double quadratic(const double a, const double b, const double c, const double x);

#endif