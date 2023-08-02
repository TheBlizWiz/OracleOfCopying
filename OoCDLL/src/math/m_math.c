#include "m_math.h"
#include <math.h>

double hypot3(double x, double y, double z) {
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