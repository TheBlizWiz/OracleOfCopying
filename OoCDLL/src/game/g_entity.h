#ifndef G_ENTITY_H
#define G_ENTITY_H
/*
#include "defs/d_common.h"
#include "render/r_image.h"
#include "game/g_enums.h"
#include "game/g_hitbox.h"

typedef struct {

    EntityClass_e eclass;
    i32           posx;
    i32           posy;
    i16           posz;
    i32           flags;
    Hitbox_t      hbox;


    // See g_object.h for my current notes / thoughts on this...
    union {
        void                *tovoid     [128];
        const void          *toconstvoid[128];
        struct FireballData *tofireball [128];
    } classdata;

} Entity_t;

typedef struct {
    u16             key;
    EntityNode_t   *prev;
    EntityNode_t   *next;
    EntityNode_t   *dom;
    EntityNode_t   *sub;
    Entity_t       *obj;
} EntityNode_t;
*/
#endif