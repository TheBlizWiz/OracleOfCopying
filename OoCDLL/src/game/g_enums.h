#ifndef G_ENUMS_H
#define G_ENUMS_H

typedef enum {
    EMPTY,
    WALL,
    TORCH_WALL,
    BLOCK_STATIC,
    STATUE_STATIC,
    CRYSTAL_STATIC,
    PILLAR_2D,
    TORCH_WALL_2D
} TileClass_e;

typedef enum {
    PLAYER_START,
    ENEMY_SPAWNER,
    WALL_BREAKABLE,
    FLOOR_BREAKABLE,
    WATER_SHALLOW,
    WATER_NORMAL,
    WATER_DEEP,
    STAIRS,
    GRASS_NORMAL,
    GRASS_REGROWABLE,
    POT,
    PIT,
    TORCH_UNLIT,
    TORCH_LIT,
    BLOCK_PUSHABLE,
    BLOCK_LOCKED,
    BLOCK_BREAKABLE,
    BLOCK_MOVING,
    DOOR_SHUTTER,
    DOOR_LOCKED,
    DOOR_MINECART,
    MOVING_PLATFORM,
    CHEST,
    EYE_STATUE,
    OWL_STATUE,
    PEDESTAL,
    FLOOR_BUTTON,
    LEVER,
    MINECART_TRACK_REGULAR,
    MINECART_TRACK_SWITCHABLE,
    MINECART_TRACK_END,
    PEDESTAL,
    BRIDGE,
    FLOOR_SPIKES,
    FLOOR_SPIKES_2D,
    LADDER_2D
} ObjectClass_e;

typedef enum {
    TRIGGER_NEVER,
    TRIGGER_ONCE,
    TRIGGER_ANYTIME
} TriggerType_e;

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