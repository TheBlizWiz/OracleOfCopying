#include <stdio.h>

#include "SDL.h"
#include "SDL_image.h"

#include "oocdll.h"

Error_t _app_start(App_t *ooc, int initflags, int wdwflags, int rdrflags);
Error_t _app_stop(App_t *ooc, int initflags);
Error_t _app_doevents(SDL_Event *evt);

int main(int argc, char *argv[]);