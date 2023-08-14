#ifndef M_VECTOR_H
#define M_VECTOR_H

#include "defs/d_common.h"

// TODO: how to make generics out of all of these?
// idk how to do _Generic with more than one generic parameter

//#define vec_add .
//#define vec_subtract .
//#define vec_multiply .
//#define vec_divide .
//#define vec_dot .

#define vec_length(v) _Generic((v), \
struct _TWO_DOUBLES: vec2_length(v), \
struct _THREE_DOUBLES: vec3_length(v), \
default: default_fail(&v) \
)(v)

#define vec_angle(v) _Generic((v), \
struct _TWO_DOUBLES: vec2_length(v), \
struct _THREE_DOUBLES: vec3_length(v), \
default: default_fail(&v) \
)(v)

#define vec_normalize(v) _Generic((v), \
struct _TWO_DOUBLES: vec2_normalize(v), \
struct _THREE_DOUBLES: vec3_normalize(v), \
default: default_fail(&v) \
)(v)

DLLINCLUDE void default_fail(void *v);

DLLINCLUDE const double vec2_length(const Vector2 v);
DLLINCLUDE const double vec3_length(const Vector3 v);

DLLINCLUDE const Angle2 vec2_angle(const Vector2 v);
DLLINCLUDE const Angle2 vec3_angle(const Vector3 v);

DLLINCLUDE const Vector2 vec2_normalize(Vector2 v);
DLLINCLUDE const Vector3 vec3_normalize(Vector3 v);

DLLINCLUDE const double vec2_dot(const Vector2 va, const Vector2 vb);
DLLINCLUDE const double vec3_dot(const Vector3 va, const Vector3 vb);

DLLINCLUDE const Vector3 vec3_cross(const Vector3 va, const Vector3 vb);

DLLINCLUDE const Vector2 vec2_add(const Vector2 v, const double d);
DLLINCLUDE const Vector3 vec3_add(const Vector3 v, const double d);

DLLINCLUDE const Vector2 vec2_subtract(const Vector2 v, const double d);
DLLINCLUDE const Vector3 vec3_subtract(const Vector3 v, const double d);

DLLINCLUDE const Vector2 vec2_multiply(const Vector2 v, const double d);
DLLINCLUDE const Vector3 vec3_multiply(const Vector3 v, const double d);

DLLINCLUDE const Vector2 vec2_divide(const Vector2 v, const double d);
DLLINCLUDE const Vector3 vec3_divide(const Vector3 v, const double d);

DLLINCLUDE const Vector2 vec2_vadd(const Vector2 va, const Vector2 vb);
DLLINCLUDE const Vector3 vec3_vadd(const Vector3 va, const Vector3 vb);

DLLINCLUDE const Vector2 vec2_vsubtract(const Vector2 va, const Vector2 vb);
DLLINCLUDE const Vector3 vec3_vsubtract(const Vector3 va, const Vector3 vb);

DLLINCLUDE const Vector2 vec2_vmultiply(const Vector2 va, const Vector2 vb);
DLLINCLUDE const Vector3 vec3_vmultiply(const Vector3 va, const Vector3 vb);

DLLINCLUDE const Vector2 vec2_vdivide(const Vector2 va, const Vector2 vb);
DLLINCLUDE const Vector3 vec3_vdivide(const Vector3 va, const Vector3 vb);

#endif
