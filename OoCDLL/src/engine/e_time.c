#include "e_time.h"
#include "defs/d_common.h"
#include "SDL.h"

Time_t time_start() {
    Time_t t = { 0 };
    t.tick = SDL_GetTicks64();
    return t;
}

void time_calc(Time_t t) {
    t.tick = SDL_GetTicks64();
    t.time = (double) t.tick / 1000.0;
}