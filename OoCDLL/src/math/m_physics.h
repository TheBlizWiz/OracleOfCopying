#ifndef M_PHYSICS_H
#define M_PHYSICS_H

#include "defs/d_common.h"
#include "game/g_entity.h"

DLLINCLUDE Error_t phys_resetforces(Entity_t *ent);

DLLINCLUDE Error_t phys_gravity(Entity_t *ent);

DLLINCLUDE Error_t phys_friction(Entity_t *ent);

DLLINCLUDE Error_t phys_calcenvironmentforces(Entity_t *ent);

DLLINCLUDE Error_t phys_integrate(Entity_t *ent, double dt);

DLLINCLUDE Error_t phys_calcobjectforces(Entity_t *ent, Vector3 v);

DLLINCLUDE State_t phys_interpolate(Entity_t *ent, double alpha);

// Error_t phys_docollisionorsomethingidk(Entity_t *ent, Hitbox_t hbox, ???);

// Error_t phys_calculate(Entity_t *ent, double dt);

#endif