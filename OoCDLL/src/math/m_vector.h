#ifndef M_VECTOR_H
#define M_VECTOR_H

#include "defs/d_common.h"

DLLINCLUDE double vec2_length(Vector2 v);
DLLINCLUDE double vec3_length(Vector3 v);

DLLINCLUDE void vec2_normalize(Vector2 v);
DLLINCLUDE void vec3_normalize(Vector3 v);

DLLINCLUDE double vec2_dot(Vector2 u, Vector2 v);
DLLINCLUDE double vec3_dot(Vector3 u, Vector3 v);

DLLINCLUDE void vec2_add(Vector2 v, double d);
DLLINCLUDE void vec3_add(Vector3 v, double d);

DLLINCLUDE void vec2_subtract(Vector2 v, double d);
DLLINCLUDE void vec3_subtract(Vector3 v, double d);

DLLINCLUDE void vec2_multiply(Vector2 v, double d);
DLLINCLUDE void vec3_multiply(Vector3 v, double d);

DLLINCLUDE void vec2_divide(Vector2 v, double d);
DLLINCLUDE void vec3_divide(Vector3 v, double d);

#endif
