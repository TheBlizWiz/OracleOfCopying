#include <stdio.h>
#include <stdlib.h>

#include "d_common.h"
#include "g_hitbox.h"

int main(void) {

    Hitbox_t hbox = hbox_newdefault();

    u8 *A = hbox_getpoint(hbox.yxA);
    u8 *B = hbox_getpoint(hbox.yxB);
    u8 *C = hbox_getpoint(hbox.yxC);
    u8 *D = hbox_getpoint(hbox.yxD);

    printf("(%i, %i)\n", A[0], A[1]);
    printf("(%i, %i)\n", B[0], B[1]);
    printf("(%i, %i)\n", C[0], C[1]);
    printf("(%i, %i)\n\n\n\n", D[0], D[1]);
 
    printf("%i\n", hbox.yxA);
    printf("%i\n", hbox.yxB);
    printf("%i\n", hbox.yxC);
    printf("%i\n", hbox.yxD);
    printf("%i\n", hbox.zbottom);
    printf("%i\n", hbox.ztop);

    free(A);
    free(B);
    free(C);
    free(D);

    return 0;
}