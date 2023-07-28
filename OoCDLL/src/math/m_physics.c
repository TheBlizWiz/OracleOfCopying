#include "m_physics.h"
#include "defs/d_constants.h"

#include "game/g_player.h"

Error_t phys_resetforces(Entity_t *ent) {
    if (ent) {
        ent->force = (Vector3){ 0.0 };
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t phys_integrate(Entity_t *ent, double dt) {
    if (ent) {
        if (dt > 0.0) {
            if (ent->mass > 0.0) {
                ent->acceleration.x = ent->force.x / ent->mass;
                ent->acceleration.y = ent->force.y / ent->mass;
                ent->acceleration.z = ent->force.z / ent->mass;

                ent->velocity.x += ent->acceleration.x * dt;
                ent->velocity.y += ent->acceleration.y * dt;
                ent->velocity.z += ent->acceleration.z * dt;

                ent->position.x += ent->velocity.x * dt;
                ent->position.y += ent->velocity.y * dt;
                ent->position.z += ent->velocity.z * dt;

                // temporary, replace with actual ground collision later
                if (ent->position.z < 0.0) {
                    ent->position.z = 0.0;
                }

                ent->force.x = 0.0;
                ent->force.y = 0.0;
                ent->force.z = 0.0;

                return ERROR_NOERROR;
            }
            else {
                errprintf("ERROR: entity mass is <= 0.0 grams, can't do physics...\n");
                return ERROR_MATH_INVALIDVALUE;
            }
        }
        else {
            errprintf("ERROR: delta time dt is <= 0, can't do physics...\n");
            return ERROR_MATH_INVALIDVALUE;
        }
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t phys_gravity(Entity_t *ent) {
    // TODO: actual gravity function with collision n stuff

    if (ent) {
        ent->force.z -= GRAVITY_Z_FORCE;
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t phys_calcenvironmentforces(Entity_t *ent) {
    if (ent) {
        Error_t e1 = phys_gravity(ent);
        // Error_t e2 = phys_wind or something idk
        return ERROR_NOERROR + e1;
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t phys_calcobjectforces(Entity_t *ent, Vector3 v) {
    if (ent) {
        ent->force.x += v.x;
        ent->force.y += v.y;
        ent->force.z += v.z;
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}