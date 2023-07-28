#include "e_time.h"
#include "defs/d_common.h"
#include "SDL.h"

void time_start(Time_t t) {
    zeroset(&t, sizeof(Time_t));
    t.tick = SDL_GetTicks64();
}

void time_calc(Time_t t) {
    u64 currtick = SDL_GetTicks64();
    double frametime = (double) (currtick - t.tick) / 1000.0;
    t.time = (double) currtick / 1000.0;
    t.accumtime += frametime;
    t.tick = currtick;
}