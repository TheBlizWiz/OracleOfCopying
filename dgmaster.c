#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "d_string.h"
#include "d_utils.h"
#include "d_common.h"
#include "d_temp.h"

int main(void) {

    String_t kb = str_new(NULL);
    String_t tmp = str_new(NULL);
    Strsize_t read = 0;

    const char *ext = "exit";
    const char *nme = "name";
    const char *elv = "elevation";
    const char *hbx = "hitbox";
    const char *img = "image texture";
    const char *alp = "alpha texture";
    const char *bgt = "background texture";
    const char *dne = "done";

    StaticTile *stile = NULL;

    String_t stile_name = str_new(NULL);
    String_t stile_imgtex = str_new(NULL);
    String_t stile_alptex = str_new(NULL);
    String_t stile_flrtex = str_new(NULL);
    bool stile_hasalp = false;
    Hitbox_t stile_hbx;
    i16 stile_elev;

    printf("Type \"exit\" to exit...\n");
    bool b = true;
    printf("Making a new static tile block...\n");
    printf("Enter a response: ");
    while(b) {
        read = file_readline(&kb, stdin);

        if(read < 0) {
            printf("Something went wrong...\n");
            printf("Error value is %ld\n", read);
            return 1;
        }

        str_tolower(kb);
        str_sanitize(kb);

        u8 cmp = 0;
        u8 cmp_ext = str_equals(kb, ext);
        u8 cmp_nme = str_equals(kb, nme);
        u8 cmp_elv = str_equals(kb, elv);
        u8 cmp_hbx = str_equals(kb, hbx);
        u8 cmp_img = str_equals(kb, img);
        u8 cmp_alp = str_equals(kb, alp);
        u8 cmp_bgt = str_equals(kb, bgt);
        u8 cmp_dne = str_equals(kb, dne);
        cmp = cmp_ext << 0 | cmp;
        cmp = cmp_nme << 1 | cmp;
        cmp = cmp_elv << 2 | cmp;
        cmp = cmp_hbx << 3 | cmp;
        cmp = cmp_img << 4 | cmp;
        cmp = cmp_alp << 5 | cmp;
        cmp = cmp_bgt << 6 | cmp;
        cmp = cmp_dne << 7 | cmp;

        switch(cmp) {
            case 1:
                printf("Exiting...\n");
                b = false;
                break;
            case 2:
                printf("Enter a name for the tile...");

                read = file_readline(&stile_name, stdin);

                if(read < 0) {
                    printf("Something went wrong...\n");
                    printf("Error value is %ld\n", read);
                    return 1;
                }

                str_sanitize(stile_name);

                printf("Saved name as %s\n\n\nEnter a new response...", stile_name);
                break;
            case 4:
                printf("Numbers only!\n");
                printf("Enter an elevation for the tile...");

                read = file_readline(&tmp, stdin);

                if(read < 0) {
                    printf("Something went wrong...\n");
                    printf("Error value is %ld\n", read);
                    return 1;
                }

                str_sanitize(tmp);

                stile_elev = (i16) atoi(tmp);

                printf("Saved elevation...\n\n\nEnter a new response...");
                break;
            case 8:
                u8 xA, xB, xC, xD, yA, yB, yC, yD;
                i16 zt, zb;

                for(int j = 0; j < 8; j++) {
                    printf("Numbers only!\n");

                    switch(j) {
                        case 0:
                        case 2:
                        case 4:
                        case 6:
                            printf("Enter the x coord for point ");
                            break;
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                            printf("Enter the y coord for point ");
                            break;
                        default:
                            printf("how did we get here?\n");
                    }

                    switch(j) {
                        case 0:
                        case 1:
                            printf("A (range: 0-32)...");
                            break;
                        case 2:
                        case 3:
                            printf("B (range: 0-32)...");
                            break;
                        case 4:
                        case 5:
                            printf("C (range: 0-32)...");
                            break;
                        case 6:
                        case 7:
                            printf("D (range: 0-32)...");
                            break;
                        default:
                            printf("how did we get here?\n");
                    }

                    read = file_readline(&tmp, stdin);

                    if(read < 0) {
                        printf("Something went wrong...\n");
                        printf("Error value is %ld\n", read);
                        return 1;
                    }

                    str_sanitize(tmp);

                    switch(j) {
                        case 0:
                            xA = (u8) atoi(tmp);
                            break;
                        case 1:
                            yA = (u8) atoi(tmp);
                            break;
                        case 2:
                            xB = (u8) atoi(tmp);
                            break;
                        case 3:
                            yB = (u8) atoi(tmp);
                            break;
                        case 4:
                            xC = (u8) atoi(tmp);
                            break;
                        case 5:
                            yC = (u8) atoi(tmp);
                            break;
                        case 6:
                            xD = (u8) atoi(tmp);
                            break;
                        case 7:
                            yD = (u8) atoi(tmp);
                            break;
                        default:
                            printf("you must've put in something wrong... leaving as default value...\n");
                    }

                    str_clear(tmp);
                }

                printf("Numbers only!\n");
                printf("Enter the elevation of the bottom face of the hitbox (range -32768 to 32767)...");
                
                read = file_readline(&tmp, stdin);

                if(read < 0) {
                    printf("Something went wrong...\n");
                    printf("Error value is %ld\n", read);
                    return 1;
                }

                str_sanitize(tmp);

                zb = (i16) atoi(tmp);
                str_clear(tmp);

                printf("Numbers only!\n");
                printf("Enter the elevation of the top face of the hitbox (range -32768 to 32767)...");
                
                read = file_readline(&tmp, stdin);

                if(read < 0) {
                    printf("Something went wrong...\n");
                    printf("Error value is %ld\n", read);
                    return 1;
                }

                str_sanitize(tmp);

                zt = (i16) atoi(tmp);
                str_clear(tmp);

                stile_hbx = hbox_new(xA, xB, xC, xD, yA, yB, yC, yD, zt, zb);
                printf("Saved hitbox...\n\n\nEnter a new response...");
                break;
            case 16:
                printf("Enter the full file path name for the base texture image....");

                read = file_readline(&stile_imgtex, stdin);

                if(read < 0) {
                    printf("Something went wrong...\n");
                    printf("Error value is %ld\n", read);
                    return 1;
                }

                str_sanitize(stile_imgtex);
                printf("Saved file path for base image as %s\n\n\nEnter a new response...", stile_imgtex);
                break;
            case 32:
                stile_hasalp = true;
                printf("Enter the full file path name for the base texture image mask (alpha image)....");

                read = file_readline(&stile_alptex, stdin);

                if(read < 0) {
                    printf("Something went wrong...\n");
                    printf("Error value is %ld\n", read);
                    return 1;
                }

                str_sanitize(stile_imgtex);
                printf("Saved file path for alpha image as %s\n\n\nEnter a new response...", stile_alptex);
                break;
            case 64:
                printf("Enter the full file path name for the floor texture image....");

                read = file_readline(&stile_flrtex, stdin);

                if(read < 0) {
                    printf("Something went wrong...\n");
                    printf("Error value is %ld\n", read);
                    return 1;
                }

                str_sanitize(stile_imgtex);
                printf("Saved file path for floor image as %s\n\n\nEnter a new response...", stile_flrtex);
                break;
            case 128:
                printf("OK! Making new tile from inputted information....");
                stile = stctile_new(stile_name, stile_elev, stile_hbx, stile_hasalp, stile_imgtex, stile_alptex, stile_flrtex);
                printf("...done!\n");
                printf("Now type \"exit\" to exit Dungeon Master..\n.");
                break;
            default:
                printf("Invalid response. Try again.\n");
        }

        str_clear(kb);
    }

    if(kb != NULL) {
        str_free(kb);
    }

    if(tmp != NULL) {
        str_free(tmp);
    }

printf("\n\n\n\n\n\n\n\n\nMoment of truth...\n");
stctile_printf(stile);

if(stile != NULL) {
    stctile_free(stile);
}

    return 0;
}