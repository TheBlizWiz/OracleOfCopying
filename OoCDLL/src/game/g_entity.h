#ifndef G_ENTITY_H
#define G_ENTITY_H

#include "defs/d_common.h"

DLLINCLUDE typedef struct Entity Entity_t;
DLLINCLUDE typedef struct State State_t;

struct State {
    Point3 position;
    Vector3 velocity;
    Vector3 acceleration;
};

struct Entity {
    double mass;
    Vector3 force;

    struct State prevstate;
    struct State currstate;
};

DLLINCLUDE Error_t state_update(Entity_t *ent);

#endif