#include "math/m_vector.h"
#include "math/m_math.h"
#include <math.h>
#include "defs/d_macros.h"

void default_fail(void *v) {
    errprintf("ERROR: _Generic went to default case, possibly bad side effects may occurr now!\n");
}

const double vec2_length(const Vector2 v) {
    return hypot(v.x, v.y);
}

const double vec3_length(const Vector3 v) {
    return hypot3(v.x, v.y, v.z);
}

const Angle2 vec2_angle(const Vector2 v) {
    return (Angle2) {
        .pitch = atan2(v.y, v.x), .yaw = 0.0
    };
}

const Angle2 vec3_angle(const Vector3 v) {
    return (Angle2) {
        .pitch = atan2(v.x, v.y), .yaw = acos(v.z / hypot3(v.x, v.y, v.z))
    };
}

const Vector2 vec2_normalize(const Vector2 v) {
    double n = hypot(v.x, v.y);
    Vector2 vn = { 0.0 };
    if (n != 0.0 && n != INFINITY && n != NAN) {
        vn.x = v.x / n;
        vn.y = v.y / n;
    }
    return vn;
}

const Vector3 vec3_normalize(const Vector3 v) {
    double n = hypot3(v.x, v.y, v.z);
    Vector3 vn = { 0.0 };
    if (n != 0.0 && n != INFINITY && n != NAN) {
        vn.x = v.x / n;
        vn.y = v.y / n;
        vn.z = v.z / n;
    }
    return vn;
}

const double vec2_dot(const Vector2 va, const Vector2 vb) {
    return (va.x * vb.x) + (va.y * vb.y);
}

const double vec3_dot(const Vector3 va, const Vector3 vb) {
    return (va.x * vb.x) + (va.y * vb.y) + (va.z * vb.z);
}

const Vector3 vec3_cross(const Vector3 va, const Vector3 vb) {
    Vector3 vn = { 0.0 };
    vn.x = (va.y * vb.z) - (va.z * vb.y);
    vn.y = (va.z * vb.x) - (va.x * vb.z);
    vn.z = (va.x * vb.y) - (va.y * vb.x);
    return vn;
}

const Vector2 vec2_add(const Vector2 v, const double d) {
    Vector2 vn = { 0.0 };
    vn.x = v.x + d;
    vn.y = v.y + d;
    return vn;
}

const Vector3 vec3_add(const Vector3 v, const double d) {
    Vector3 vn = { 0.0 };
    vn.x = v.x + d;
    vn.y = v.y + d;
    vn.z = v.z + d;
    return vn;
}

const Vector2 vec2_subtract(const Vector2 v, const double d) {
    Vector2 vn = { 0.0 };
    vn.x = v.x - d;
    vn.y = v.y - d;
    return vn;
}

const Vector3 vec3_subtract(const Vector3 v, const double d) {
    Vector3 vn = { 0.0 };
    vn.x = v.x - d;
    vn.y = v.y - d;
    vn.z = v.z - d;
    return vn;
}

const Vector2 vec2_multiply(const Vector2 v, const double d) {
    Vector2 vn = { 0.0 };
    vn.x = v.x * d;
    vn.y = v.y * d;
    return vn;
}

const Vector3 vec3_multiply(const Vector3 v, const double d) {
    Vector3 vn = { 0.0 };
    vn.x = v.x * d;
    vn.y = v.y * d;
    vn.z = v.z * d;
    return vn;
}

const Vector2 vec2_divide(const Vector2 v, const double d) {
    Vector2 vn = { 0.0 };
    if (d != 0.0) {
        vn.x = v.x / d;
        vn.y = v.y / d;
    }
    return vn;
}

const Vector3 vec3_divide(const Vector3 v, const double d) {
    Vector3 vn = { 0.0 };
    if (d != 0.0) {
        vn.x = v.x / d;
        vn.y = v.y / d;
        vn.z = v.z / d;
    }
    return vn;
}

const Vector2 vec2_vadd(const Vector2 va, const Vector2 vb) {
    Vector2 vn = { 0.0 };
    vn.x = va.x + vb.x;
    vn.y = va.y + vb.y;
    return vn;
}

const Vector3 vec3_vadd(const Vector3 va, const Vector3 vb) {
    Vector3 vn = { 0.0 };
    vn.x = va.x + vb.x;
    vn.y = va.y + vb.y;
    vn.z = va.z + vb.z;
    return vn;

}

const Vector2 vec2_vsubtract(const Vector2 va, const Vector2 vb) {
    Vector2 vn = { 0.0 };
    vn.x = va.x - vb.x;
    vn.y = va.y - vb.y;
    return vn;
}

const Vector3 vec3_vsubtract(const Vector3 va, const Vector3 vb) {
    Vector3 vn = { 0.0 };
    vn.x = va.x - vb.x;
    vn.y = va.y - vb.y;
    vn.z = va.z - vb.z;
    return vn;
}

const Vector2 vec2_vmultiply(const Vector2 va, const Vector2 vb) {
    Vector2 vn = { 0.0 };
    vn.x = va.x * vb.x;
    vn.y = va.y * vb.y;
    return vn;
}

const Vector3 vec3_vmultiply(const Vector3 va, const Vector3 vb) {
    Vector3 vn = { 0.0 };
    vn.x = va.x * vb.x;
    vn.y = va.y * vb.y;
    vn.z = va.z * vb.z;
    return vn;
}

const Vector2 vec2_vdivide(const Vector2 va, const Vector2 vb) {
    Vector2 vn = { 0.0 };
    vn.x = (vb.x != 0.0) ? va.x / vb.x : 0.0;
    vn.y = (vb.y != 0.0) ? va.y / vb.y : 0.0;
    return vn;
}

const Vector3 vec3_vdivide(const Vector3 va, const Vector3 vb) {
    Vector3 vn = { 0.0 };
    vn.x = (vb.x != 0.0) ? va.x / vb.x : 0.0;
    vn.y = (vb.y != 0.0) ? va.y / vb.y : 0.0;
    vn.z = (vb.z != 0.0) ? va.z / vb.z : 0.0;
    return vn;
}