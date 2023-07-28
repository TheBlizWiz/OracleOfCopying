#ifndef M_PHYSICS_H
#define M_PHYSICS_H

#include "defs/d_common.h"
#include "game/g_entity.h"

Error_t phys_resetforces(Entity_t *ent);

Error_t phys_gravity(Entity_t *ent);

Error_t phys_calcenvironmentforces(Entity_t *ent);

Error_t phys_integrate(Entity_t *ent, double dt);

// Error_t phys_docollisionorsomethingidk(Entity_t *ent, Hitbox_t hbox, ???);

Error_t phys_calculate(Entity_t *ent, double dt);

#endif