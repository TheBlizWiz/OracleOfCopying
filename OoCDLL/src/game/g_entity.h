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

    // function pointer to this entity's physics handler
    // this function pointer should accept a Vector3
    // and return an Error_t error code
    Error_t(*physicshandler)(Vector3 v);
};

#endif