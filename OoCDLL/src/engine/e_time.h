#ifndef E_TIME_H
#define E_TIME_H

#include "defs/d_common.h"

DLLINCLUDE typedef struct Time Time_t;

struct Time {
    u64 tick;
    double time;
    double accumtime;
};

void time_start(Time_t t);
void time_calc(Time_t t);

#endif