#ifndef G_OBJECT_H
#define G_OBJECT_H

#include <defs/d_common.h>
#include <render/r_image.h>

#include "g_oclasses.h"
#include "g_enums.h"
#include "g_hitbox.h"

typedef struct {

    ObjectClass_e oclass;
    i8            roomid;
    i16           gposx;
    i16           gposy;
    i16           elev;
    i32           flags;
    Hitbox_t      hbox;
    Image_t     **otex;
    
    /*
    The way I plan on this working is to make a common
    block of memory after all of the above fields that's the
    same size, wasted memory be damned

    In this block object-specific data is held here
    For a chest, it would be what's in it, how much,
    how it spawns, etc

    For a door it would be how it opens, if it stays open,
    if its locked, etc

    Basically it's a space for object scripting
    Based off of Mario 64

    TODO: how many bytes max do I need? 128 for now...

    TODO: so how does mario 64 use these unions? it looks
          like a pointer to an array of structs but thats
          not how it works in memory - its a block of memory
          after any object that holds object specific fields
          specifically 80 bytes after the "common" fields that
          hold whatever is needed

          its written like "struct Object *asObject[0x50]" but
          how its written and how it works dont seem to match...

          need to look into it...
    */
    union { 
        void                   *tovoid       [128];
        const void             *toconstvoid  [128];
        struct ChestData       *tochest      [128];
        struct DoorData        *todoor       [128];
        struct PushBlockData   *topushblock  [128];
        struct FloorButtonData *toflrbutton  [128];
        struct BombWallData    *tobombwall   [128];
        struct CrateData       *tocrate      [128];
        struct PitData         *topit        [128];
        struct PlayerSpawnData *toplayerspawn[128];
        struct EnemySpawnData  *toenemyspawn [128];

        /* 
          TODO: some way to keep this auto made or
                at least nice and organized?
        */

    } classdata;

} Object_t;

#endif