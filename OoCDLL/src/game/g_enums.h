#ifndef G_ENUMS_H
#define G_ENUMS_H

#include "defs/d_common.h"

DLLINCLUDE typedef enum TileType TileType_e;
DLLINCLUDE typedef enum ObjectType ObjectType_e;
DLLINCLUDE typedef enum ActorType ActorType_e;
DLLINCLUDE typedef enum TriggerType TriggerType_e;

enum TileType {
    EMPTY,
    WALL,
    TORCH_WALL,
    BLOCK_STATIC,
    STATUE_STATIC,
    CRYSTAL_STATIC,
    PILLAR_2D,
    TORCH_WALL_2D
};

enum ObjectType {
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
    BRIDGE,
    FLOOR_SPIKES,
    FLOOR_SPIKES_2D,
    LADDER_2D
};

enum ActorType {
    PLAYER,
    SLIME,
    BAT,
    SKELETON
};


// what were these even used for again?
enum TriggerType {
    TRIGGER_NEVER,
    TRIGGER_ONCE,
    TRIGGER_ANYTIME
};

#endif