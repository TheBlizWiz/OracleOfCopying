#include "m_physics.h"
#include "defs/d_constants.h"
#include "defs/d_macros.h"

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
                ent->currstate.acceleration.x = ent->force.x / ent->mass;
                ent->currstate.acceleration.y = ent->force.y / ent->mass;
                ent->currstate.acceleration.z = ent->force.z / ent->mass;

                ent->currstate.velocity.x += ent->currstate.acceleration.x * dt;
                ent->currstate.velocity.y += ent->currstate.acceleration.y * dt;
                ent->currstate.velocity.z += ent->currstate.acceleration.z * dt;

                ent->currstate.position.x += ent->currstate.velocity.x * dt;
                ent->currstate.position.y += ent->currstate.velocity.y * dt;
                ent->currstate.position.z += ent->currstate.velocity.z * dt;

                // temporary, replace with actual ground collision later
                if (ent->currstate.position.z < 0.0) {
                    ent->currstate.position.z = 0.0;
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

State_t phys_interpolate(Entity_t *ent, double alpha) {
    State_t tmpstate = { 0.0 };

    tmpstate.position.x = (ent->currstate.position.x * alpha) + (ent->prevstate.position.x * (1.0 - alpha));
    tmpstate.position.y = (ent->currstate.position.y * alpha) + (ent->prevstate.position.y * (1.0 - alpha));
    tmpstate.position.z = (ent->currstate.position.z * alpha) + (ent->prevstate.position.z * (1.0 - alpha));

    return tmpstate;
}