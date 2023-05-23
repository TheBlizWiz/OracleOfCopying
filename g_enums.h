#ifndef G_ENUMS_H
#define G_ENUMS_H

typedef enum {
    NONE,
    EMPTY,
    GENERIC,
    WALL,
    DECORATION,
    BLOCK
} TileClass_e;

typedef enum {
    NONE,
    BLOCK,
    BREAKABLE_WALL,
    PIT,
    CHEST,
    CRATE,
    SWITCH,
    FLOOR_BUTTON,
    PATH_PUZZLE_TILE,
    DOOR,
    BRIDGE,
    SPINNER,
    PLAYER_START,
    ENEMY_SPAWNER
} ObjectClass_e

typedef enum {
    TRIGGER_NEVER,
    TRIGGER_ONCE,
    TRIGGER_ANYTIME
} TriggerType_e;

typedef enum {
    NONE,
    FIREBALL
} EntityClass_e;

/*
copied from the old d_enums.h
    typedef enum {
    NONE,
    BLOCK,
    BREAKABLE_WALL,
    PIT,
    CHEST,
    CRATE,
    SWITCH,
    FLOOR_BUTTON,
    PATH_PUZZLE_TILE,
    DOOR,
    BRIDGE,
    SPINNER,
    PLAYER_START,
    ENEMY_SPAWNER
} EntityType_t;

typedef enum {
    NONE,
    KEY,
    BOSS_KEY,
    GEM,
    WEAPON,
    EQUIP_ITEM
} ItemType_t;

typedef enum {
    NONE,
    SPEAR,
    BOW,
    BOMB,
    BOOMERANG
} WeaponType_t;

typedef enum {
    NONE,
    SHIELD,
    FEATHER,
    GLOVE,
} EquipItemType_t;

typedef enum {
    NONE,
    SLIME,
    SKELETON,
    BAT,
    ORC,
    GHOST,
    WIZARD,
    ZOMBIE,
    BLADE_TRAP
} EnemyType_t;

typedef enum {
    NONE,
    DRAGON,
    HYDRA,
    SNAKE,
    EYEBALL
} BossEnemyType_t;

typedef enum {
    NONE,
    BIG_SKELETON,
    BIG_SLIME
} MiniBossEnemyType_t;
*/

#endif