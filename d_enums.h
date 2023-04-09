// not sure if any of these need a none type at the top
// but im making these before i know what each will look like
// so who knows

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