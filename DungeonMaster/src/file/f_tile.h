#ifndef F_TILE_H
#define F_TILE_H

#include "oocdll.h"

Error_t dg_writetile(cJSON *dgjsonfile, Tile_t *t, const char *tiletex, const char *floortex);

#endif