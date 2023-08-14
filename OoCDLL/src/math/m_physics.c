#include "m_physics.h"
#include "m_vector.h"
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

                ent->currstate.acceleration = vec3_divide(ent->force, ent->mass);

                if (ent->currstate.acceleration.x > 0 && ent->currstate.acceleration.x < 0.1) {
                    ent->currstate.acceleration.x = 0.0;
                }
                if (ent->currstate.acceleration.x < 0 && ent->currstate.acceleration.x > -0.1) {
                    ent->currstate.acceleration.x = 0.0;
                }
                if (ent->currstate.acceleration.y > 0 && ent->currstate.acceleration.y < 0.1) {
                    ent->currstate.acceleration.y = 0.0;
                }
                if (ent->currstate.acceleration.y < 0 && ent->currstate.acceleration.y > -0.1) {
                    ent->currstate.acceleration.y = 0.0;
                }

                ent->currstate.velocity = vec3_vadd(ent->currstate.velocity, vec3_multiply(ent->currstate.acceleration, dt));

                if (ent->currstate.velocity.x > 0 && ent->currstate.velocity.x < 0.1) {
                    ent->currstate.velocity.x = 0.0;
                }
                if (ent->currstate.velocity.x < 0 && ent->currstate.velocity.x > -0.1) {
                    ent->currstate.velocity.x = 0.0;
                }
                if (ent->currstate.velocity.y > 0 && ent->currstate.velocity.y < 0.1) {
                    ent->currstate.velocity.y = 0.0;
                }
                if (ent->currstate.velocity.y < 0 && ent->currstate.velocity.y > -0.1) {
                    ent->currstate.velocity.y = 0.0;
                }

                ent->currstate.position = vec3_vadd(ent->currstate.position, vec3_multiply(ent->currstate.velocity, dt));

                // temporary, replace with actual ground collision later
                if (ent->currstate.position.z < 0.0) {
                    ent->currstate.position.z = 0.0;
                }



                ent->force = (Vector3){ 0.0 };

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

Error_t phys_friction(Entity_t *ent) {
    if (ent) {
        if (ent->currstate.velocity.x > 0.0) {
            ent->force.x -= FRICTION_X_FORCE;
        }
        if (ent->currstate.velocity.x < 0.0) {
            ent->force.x += FRICTION_X_FORCE;
        }
        if (ent->currstate.velocity.y > 0.0) {
            ent->force.y -= FRICTION_Y_FORCE;
        }
        if (ent->currstate.velocity.y < 0.0) {
            ent->force.y += FRICTION_Y_FORCE;
        }

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
        Error_t e2 = phys_friction(ent);
        // Error_t e2 = phys_wind or something idk
        return ERROR_NOERROR + e1 + e2;
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}

Error_t phys_calcobjectforces(Entity_t *ent, Vector3 v) {
    if (ent) {
        ent->force = vec3_vadd(ent->force, v);
        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}

State_t phys_interpolate(Entity_t *ent, double alpha) {
    State_t tmpstate = { 0.0 };

    tmpstate.position = vec3_vadd(vec3_multiply(ent->currstate.position, alpha), vec3_multiply(ent->prevstate.position, (1.0 - alpha)));

    return tmpstate;
}