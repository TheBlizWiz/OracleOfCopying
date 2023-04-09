#include <stdio.h>
#include <stdlib.h>

#include "d_temp.h"
#include "g_hitbox.h"

StaticTile *stctile_new(String_t nme, i16 elv, Hitbox_t hbx, bool hasalp, String_t btex, String_t atex, String_t ftex) {
    StaticTile *stct = (StaticTile *) malloc(sizeof(StaticTile));
    stct->name = nme;
    stct->elevation = elv;
    stct->hitbox = hbx;
    stct->hasalpha = hasalp;
    stct->basetex = btex;
    stct->alphatex = atex;
    stct->floortex = ftex;
    return stct;
}

void stctile_free(StaticTile *stct) {
    if(stct->hasalpha) {
        str_free(stct->alphatex);
    }
    str_free(stct->name);
    str_free(stct->basetex);
    str_free(stct->floortex);

    free(stct);
}

void stctile_printf(StaticTile *stct) {
    u8 *ptA = hbox_getpoint(stct->hitbox.yxA);
    u8 *ptB = hbox_getpoint(stct->hitbox.yxB);
    u8 *ptC = hbox_getpoint(stct->hitbox.yxC);
    u8 *ptD = hbox_getpoint(stct->hitbox.yxD);

    if(stct->hasalpha) {
        printf("Static Tile\n\tName: %s\n\tElevation: %d\n\tHitbox: (%i, %i), (%i, %i), (%i, %i), (%i, %i), top = %i, bottom = %i\n\tIs Transparent: yes\n\tBase Texture: %s\n\tAlpha Texture: %s\n\tFloor Texture: %s\n",
                stct->name, stct->elevation, ptA[0], ptA[1], ptB[0], ptB[1], ptC[0], ptC[1], ptD[0], ptD[1], stct->hitbox.ztop, stct->hitbox.zbottom, stct->basetex, stct->alphatex, stct->floortex); 
    }
    else {
        printf("Static Tile\n\tName: %s\n\tElevation: %d\n\tHitbox: (%i, %i), (%i, %i), (%i, %i), (%i, %i), top = %i, bottom = %i\n\tIs Transparent: no\n\tBase Texture: %s\n\tFloor Texture: %s\n",
        stct->name, stct->elevation, ptA[0], ptA[1], ptB[0], ptB[1], ptC[0], ptC[1], ptD[0], ptD[1], stct->hitbox.ztop, stct->hitbox.zbottom, stct->basetex, stct->floortex); 
    }
    free(ptA);
    free(ptB);
    free(ptC);
    free(ptD);
}