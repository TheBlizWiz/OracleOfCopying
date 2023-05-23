typedef enum {
    // for cutscenes, no control from player allowed
    NO_CONTROL,

    // idle states, per direction
    IDLE_N,
    IDLE_S,
    IDLE_E,
    IDLE_W,

    // walking states, per direction
    WALK_N,
    WALK_S,
    WALK_E,
    WALK_W,

    // attacking states, per direction
    ATTACK_N,
    ATTACK_S,
    ATTACK_E,
    ATTACK_W,
    ATTACK_NE,
    ATTACK_SE,
    ATTACK_NW,
    ATTACK_SW,

    // taking damage states, per direction
    HURT_N,
    HURT_S,
    HURT_E,
    HURT_W,



} PlayerAState_e