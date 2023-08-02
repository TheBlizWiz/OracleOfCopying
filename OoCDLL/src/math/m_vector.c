#include "math/m_vector.h"
#include "math/m_math.h"
#include <math.h>

double vec2_length(Vector2 v) {
    return hypot(v.x, v.y);
}

double vec3_length(Vector3 v) {
    return hypot3(v.x, v.y, v.z);
}

void vec2_normalize(Vector2 v) {
    double n = hypot(v.x, v.y);
    if (n != 0.0) {
        v.x /= n;
        v.y /= n;
    }
}

void vec3_normalize(Vector3 v) {
    double n = hypot3(v.x, v.y, v.z);
    if (n != 0.0) {
        v.x /= n;
        v.y /= n;
        v.z /= n;
    }
}

double vec2_dot(Vector2 u, Vector2 v) {
    return u.x * v.x + u.y * v.y;
}

double vec3_dot(Vector3 u, Vector3 v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

void vec2_add(Vector2 v, double d) {
    v.x += d;
    v.y += d;
}

void vec3_add(Vector3 v, double d) {
    v.x += d;
    v.y += d;
    v.z += d;
}

void vec2_subtract(Vector2 v, double d) {
    v.x -= d;
    v.y -= d;
}

void vec3_subtract(Vector3 v, double d) {
    v.x -= d;
    v.y -= d;
    v.z -= d;
}

void vec2_multiply(Vector2 v, double d) {
    v.x *= d;
    v.y *= d;
}

void vec3_multiply(Vector3 v, double d) {
    v.x *= d;
    v.y *= d;
    v.z *= d;
}

void vec2_divide(Vector2 v, double d) {
    if (d != 0.0) {
        v.x /= d;
        v.y /= d;
    }
}

void vec3_divide(Vector3 v, double d) {
    if (d != 0.0) {
        v.x /= d;
        v.y /= d;
        v.z /= d;
    }
}