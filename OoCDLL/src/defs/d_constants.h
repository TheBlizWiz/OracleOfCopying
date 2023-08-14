#ifndef D_CONSTANTS_H
#define D_CONSTANTS_H

// ****************************
// |      CONSTANT VALUES     |
// ****************************

// used anywhere
#define NULLADDR ((void *) 0x0)

#ifdef FALSE
#undef FALSE
#define FALSE 0
#else
#define FALSE 0
#endif

#ifdef TRUE
#undef TRUE
#define TRUE 1
#else
#define TRUE 1
#endif

// used in e_app.h

// from sdl's documentation - this is how many keys SDL recognizes
// 
// most of these nobody is going to use
// like i dunno about you but i done use the scroll lock key for gaming
// and i dont even know what a "Keypad XOR" does
// but we do have to include them all so players can remap controls
// 
// the actual number of keys is 260, but 290 is the actual int value of the last key
// round to 300 to be safe...
#define MAX_KEYS 300


// how many different player actions are possible
// subject to change
#define MAX_ACTIONS 5

// player actions timer indexes

#define ACTIONS_PLAYER_MOVE_NORTH 0
#define ACTIONS_PLAYER_MOVE_SOUTH 1
#define ACTIONS_PLAYER_MOVE_EAST 2
#define ACTIONS_PLAYER_MOVE_WEST 3
#define ACTIONS_PLAYER_MOVE_JUMP 4

// default screen size - subject to change
#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600

// used in m_rng.c
#define BITMASK_12 0x03FF

// Used in d_string.h
#define NULL_CHAR_SIZE 1
#define INDEX_STR_LEN -1
#define INDEX_STR_ALLOC -2

// used in d_utils.c

// 2 MiB
#define FILE_BUFFER_SIZE 2097152

// Used in g_hitbox.h
#define A_POS_DEFAULT 0
#define B_POS_DEFAULT 32
#define C_POS_DEFAULT 8192
#define D_POS_DEFAULT 8224
#define ZT_POS_DEFAULT 255
#define ZB_POS_DEFAULT 0

// used in r_sdl.c

#define TF_NONE 0

#define TF_ROT 1
#define TF_FLIP 2
#define TF_SCL 4

#define TF_ROTFLIP 3
#define TF_ROTSCL 5
#define TF_FLIPSCL 6
#define TF_ROTFLIPSCL 7

#define MISSING_TEX_COLOR_MAGENTA 0xFFFF00FF
#define MISSING_TEX_COLOR_BLACK 0x000000FF
#define MISSING_TEX_W 32
#define MISSING_TEX_H 32
#define MISSING_TEX_WXH 1024

// used in g_player.c

// mass of player - ~160 lb in kg
#define PLAYER_MASS 72.50


// TODO: tweak these numbers until they feel just right
#define PLAYER_MOVE_X_FORCE 0.001
#define PLAYER_MOVE_Y_FORCE 0.001
#define PLAYER_MOVE_Z_FORCE 1000.0

#define PLAYER_MOVE_X_MAGIC_NUMBER 250.0
#define PLAYER_MOVE_Y_MAGIC_NUMBER 8.0

#define PLAYER_MOVE_X_MAX_VELOCITY 240.0
#define PLAYER_MOVE_Y_MAX_VELOCITY 240.0

#define GRAVITY_Z_FORCE 100.0
#define FRICTION_X_FORCE 10000.0
#define FRICTION_Y_FORCE 10000.0

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define NORTHEAST 4
#define NORTHWEST 5
#define SOUTHEAST 6
#define SOUTHWEST 7


// used in g_roomh / g_room.c
// taken from oracle of seasons

#define TILE_PX_SIZE_X 32
#define TILE_PX_SIZE_Y 32

#define ROOM_SIZE_X 16
#define ROOM_SIZE_Y 11

#define MAP_SIZE_X 16
#define MAP_SIZE_Y 16

#define ROOM_PX_SIZE_X 512.0
#define ROOM_PX_SIZE_Y 352.0


// dimensions in pixels of entire dungeon
// from ROOM_SIZE * TILE_SIZE * MAP_SIZE
/*


     G---------H
    / |      / |
   /  |     /  |
  E--------F   |
  |   |    |   |
  |   |    |   |
  |   |    |   |
  |   C----|---D
  |  /     |  /
  | /      | /
  |/       |/
  A--------B

  A = (-4096, -2816, -128)
  B = ( 4096, -2816, -128)
  C = (-4096,  2816, -128)
  D = ( 4096,  2816, -128)
  E = (-4096, -2816,  127)
  F = ( 4096, -2816,  127)
  G = (-4096,  2816,  127)
  H = ( 4096,  2816,  127)


*/

// sets the maximum bucket size for the hashmap
// more buckets --> better performance, more memory
#define MAX_ATLAS_BUCKETS 64

#define MAX_FNAME_LENGTH 256

// -------------
// | ATLASGEN  |
// -------------

#define DEFAULT_ATLAS_PADDING 0
#define DEFAULT_ATLAS_IMAGE_SIZE 1024

// ****************************
// |         ERROR CODES      |
// ****************************

// this one is special, return 0 if no errors happen
#define ERROR_NOERROR 0

#define ERROR_GENERIC 1
#define ERROR_MALLOC_NOSPACE 2
#define ERROR_REALLOC_NOSPACE 3
#define ERROR_ISNULLADDR 4
#define ERROR_ISNOTNULLADDR 5
#define ERROR_INDEX_OOB 6
#define ERROR_SWITCH_DEFAULTCASE 7
#define ERROR_INVALID_PARAMS 8
#define ERROR_SEARCH_NORESULTS 9
#define ERROR_LOGIC_CONTRADICTION 10
#define ERROR_FILE_NOTFOUND 11
#define ERROR_BUFFEROVERFLOW 12
#define ERROR_MATH_INVALIDVALUE 13


//this one is also special, return 69420 if something catastrophically bad happens...
#define ERROR_OHSHIT 69420 

#define ERROR_SDL_GENERIC 100

// used in r_app.h and r_app.c

#define ERROR_SDL_INIT_FAILURE 101
#define ERROR_SDL_CREATEWINDOW_FAILURE 102
#define ERROR_SDL_CREATERENDERER_FAILURE 103

// used in d_string.c and u_linklist.c

#define ERROR_LENGTH_INVALIDVALUE 201
#define ERROR_TGT_NOTFOUND 202

// used in e_app.c

// this isn't an error, its just a number used to tell the while loop
// in main() to stop running since SDL_QUIT was called
#define ERROR_DOEVENTS_TIMETOQUIT 999

// this error means a switch case didnt return out of app_doevents() early
// so one of the existing cases is missing a return statement
#define ERROR_DOEVENTS_SWITCHCASEDIDNTRETURN 901

// this isn't an error, this just means theres nothing to do since
// no new events happened
#define ERROR_DOEVENTS_DEFAULTCASE 900

// used in d_utils.c
// these exist because we need Size_t to intentionally be out of bounds
#define ERROR_ISNULL_FILE -1
#define ERROR_ISNULL_STRPTR -2
#define ERROR_ISVALUE_EOF -3
#define ERROR_MALLOC_NOSPACE_READLINE -4
#define ERROR_ISNOTNULL_STRPTR -5

// ****************************
// |         STRINGS          |
// ****************************
#define GAME_WINDOW_NAME "Oracle of Copying"

// -------------
// | ATLASGEN  |
// -------------

#define ATLASGEN_DEFAULT_DIR_PATH "E:\\MSVC\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures"
#define ATLASGEN_DEFAULT_OUTPUT_PATH "E:\\MSVC\\source\\repos\\OracleOfCopying\\OracleOfCopying\\textures\\atlases"

#define ATLASGEN_SIZE_ARGV "-size"
#define ATLASGEN_PAD_ARGV "-padding"
#define ATLASGEN_DIR_ARGV "-directory"
#define ATLASGEN_OUTPUT_ARGV "-output"

#endif