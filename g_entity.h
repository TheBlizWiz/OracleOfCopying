#ifndef G_ENTITY_H
#define G_ENTITY_H

#include "d_common.h"
#include "g_enums.h"
#include "g_hitbox.h"
#include "r_image.h"

typedef struct {

    EntityClass_e eclass;
    i32           aposx;
    i32           aposy;
    i16           elev;
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

#endif