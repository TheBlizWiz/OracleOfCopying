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

// Used in g_hitbox.h
#define A_POS_DEFAULT 0
#define B_POS_DEFAULT 32
#define C_POS_DEFAULT 8192
#define D_POS_DEFAULT 8224
#define ZT_POS_DEFAULT 255
#define ZB_POS_DEFAULT 0

// used in r_image.c

#define AGL_PI_HALVES 1.57079632679
#define AGL_PI 3.14159265359
#define AGL_3PI_HALVES 4.71238898038
#define AGL_2PI 6.28318530718
#define AGL_NEG_PI_HALVES -1.57079632679
#define AGL_NEG_PI -3.14159265359
#define AGL_NEG_3PI_HALVES -4.71238898038
#define AGL_NEG_2PI -6.28318530718
#define IMG_ROT_EPSILON 0.0025


// ****************************
// |         ERROR CODES      |
// ****************************

// this one is special, return 0 if no errors happen
#define ERROR_NOERROR 0

// used in r_app.h and r_app.c

#define ERROR_SDL_INIT_FAILURE 1
#define ERROR_SDL_CREATEWINDOW_FAILURE 2
#define ERROR_SDL_CREATERENDERER_FAILURE 3

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
#define ERROR_ISNULL_FILE -1
#define ERROR_ISNULL_STRPTR -2
#define ERROR_ISVALUE_EOF -3
#define ERROR_MEMORY_NOSPACE -4



// ****************************
// |         STRINGS          |
// ****************************
#define GAME_WINDOW_NAME "Oracle of Copying"




#endif