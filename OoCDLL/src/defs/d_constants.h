#ifndef D_CONSTANTS_H
#define D_CONSTANTS_H

// ****************************
// |      CONSTANT VALUES     |
// ****************************

// used anywhere
#define NULLADDR ((void *) 0x0)

//used in r_app.c
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

#define ANGLE_NEG_90 (double) -90.00

#define MISSING_TEX_COLOR_MAGENTA 0xFFFF00FF
#define MISSING_TEX_COLOR_BLACK 0x000000FF
#define MISSING_TEX_W 32
#define MISSING_TEX_H 32
#define MISSING_TEX_WXH 1024


// used in g_roomh / g_room.c
// taken from oracle of seasons

#define ROOM_SIZE_X 16
#define ROOM_SIZE_Y 11

#define MAP_SIZE_X 16
#define MAP_SIZE_Y 16

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

// this error means the default case was called, so some event happened that isnt covered
// by the listed cases
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