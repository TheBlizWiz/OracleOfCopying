#include "m_math.h"
#include <math.h>

const double hypot3(const double x, const double y, const double z) {
    if (x == INFINITY || y == INFINITY || z == INFINITY) {
        return INFINITY;
    }
    if (x == NAN || y == NAN || z == NAN) {
        return NAN;
    }

    double dx = fabs(x);
    double dy = fabs(y);
    double dz = fabs(z);
    double dtmp = 0.0;

    if (dy > dx) {
        dtmp = dx;
        dx = dy;
        dy = dtmp;
    }

    if (dz > dx) {
        dtmp = dz;
        dz = dx;
        dx = dtmp;
    }

    double dydx = dy / dx;
    double dzdx = dz / dx;

    return dx * sqrt(1 + dydx * dydx + dzdx * dzdx);

}

const double quadratic(const double a, const double b, const double c, const double x) {
    double d1 = a * x * x;
    double d2 = b * x;
    return d1 + d2 + c;
}