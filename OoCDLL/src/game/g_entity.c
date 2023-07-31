#include "g_entity.h"
#include "defs/d_macros.h"
#include "defs/d_constants.h"

Error_t state_update(Entity_t *ent) {
    if (ent) {
        ent->prevstate.position.x = ent->currstate.position.x;
        ent->prevstate.position.y = ent->currstate.position.y;
        ent->prevstate.position.z = ent->currstate.position.z;

        ent->prevstate.velocity.x = ent->currstate.velocity.x;
        ent->prevstate.velocity.y = ent->currstate.velocity.y;
        ent->prevstate.velocity.z = ent->currstate.velocity.z;

        ent->prevstate.acceleration.x = ent->currstate.acceleration.x;
        ent->prevstate.acceleration.y = ent->currstate.acceleration.y;
        ent->prevstate.acceleration.z = ent->currstate.acceleration.z;

        return ERROR_NOERROR;
    }
    else {
        errprintf("ERROR: Entity_t *ent is null\n");
        return ERROR_ISNULLADDR;
    }
}