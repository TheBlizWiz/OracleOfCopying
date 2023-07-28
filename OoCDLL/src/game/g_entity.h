#ifndef G_ENTITY_H
#define G_ENTITY_H

#include "defs/d_common.h"

typedef struct Entity Entity_t;

struct Entity {

    double mass;
    Vector3 force;

    Point3 position;
    Vector3 velocity;
    Vector3 acceleration;
};

#endif