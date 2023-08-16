#include "dgmaster.h"

#define PTR_CHECK(ptr) do{if(!ptr) {return i;} else {i++;}} while(0)

int main(int argc, char *argv[]) {

    int i = 1;

    const char *str0 = "ddd_walls_north.qoi";
    const char *str1 = "ddd_walls_south.qoi";
    const char *str2 = "ddd_walls_east.qoi";
    const char *str3 = "ddd_walls_west.qoi";
    const char *str4 = "ddd_walls_innercorner_ne.qoi";
    const char *str5 = "ddd_walls_innercorner_se.qoi";
    const char *str6 = "ddd_walls_innercorner_nw.qoi";
    const char *str7 = "ddd_walls_innercorner_sw.qoi";
    const char *str8 = "blank.qoi";
    const char *str9 = "ddd_floors_pit.qoi";
    const char *str10 = "ddd_floors_patterned_green.qoi";
    const char *str11 = "ddd_objects_block.qoi";


    const char *lvl0  = "5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,6\n";
    const char *lvl1  = "4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3\n";
    const char *lvl2  = "4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3\n";
    const char *lvl3  = "4,0,0,0,9,0,0,0,0,0,0,9,0,0,0,0,3\n";
    const char *lvl4  = "4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3\n";
    const char *lvl5  = "4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3\n";
    const char *lvl6  = "4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3\n";
    const char *lvl7  = "4,0,0,0,9,0,0,0,0,0,0,9,0,0,0,0,3\n";
    const char *lvl8  = "4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3\n";
    const char *lvl9  = "4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3\n";
    const char *lvl10 = "7,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,8";


    TileType_e ttype = EMPTY;
    Hitbox_t hb = hbox_newdefault();

    Tile_t *t_empty = tile_new(0, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_empty);
    
    ttype = WALL;

    Tile_t *t_wall_n = tile_new(1, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_n);
    Tile_t *t_wall_s = tile_new(2, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_s);
    Tile_t *t_wall_e = tile_new(3, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_e);
    Tile_t *t_wall_w = tile_new(4, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_w);
    Tile_t *t_wall_nw = tile_new(5, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_nw);
    Tile_t *t_wall_ne = tile_new(6, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_ne);
    Tile_t *t_wall_sw = tile_new(7, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_sw);
    Tile_t *t_wall_se = tile_new(8, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_wall_se);

    ttype = BLOCK_STATIC;

    Tile_t *t_block = tile_new(9, ttype, 1, hb, 0, NULL, NULL);
    PTR_CHECK(t_block);

    cJSON *rootjson = cJSON_CreateArray();
    PTR_CHECK(rootjson);

    dg_writetile(rootjson, t_empty, str8, str10);
    dg_writetile(rootjson, t_block, str11, str10);
    dg_writetile(rootjson, t_wall_n, str0, str9);
    dg_writetile(rootjson, t_wall_s, str1, str9);
    dg_writetile(rootjson, t_wall_e, str2, str9);
    dg_writetile(rootjson, t_wall_w, str3, str9);
    dg_writetile(rootjson, t_wall_ne, str4, str9);
    dg_writetile(rootjson, t_wall_nw, str5, str9);
    dg_writetile(rootjson, t_wall_se, str6, str9);
    dg_writetile(rootjson, t_wall_sw, str7, str9);

    char *out = cJSON_Print(rootjson);
    PTR_CHECK(out);

    FILE *fptr;
    fopen_s(&fptr, "E:\\MSVC\\source\\repos\\OracleOfCopying\\tiles.json", "wb");
    if (fptr) {
        fprintf(fptr, "%s", out);
        fclose(fptr);
    }

    FILE *fptr2;
    fopen_s(&fptr2, "E:\\MSVC\\source\\repos\\OracleOfCopying\\dungeon.dg", "wb");
    if (fptr2) {
        fprintf(fptr2, "%s", lvl0);
        fprintf(fptr2, "%s", lvl1);
        fprintf(fptr2, "%s", lvl2);
        fprintf(fptr2, "%s", lvl3);
        fprintf(fptr2, "%s", lvl4);
        fprintf(fptr2, "%s", lvl5);
        fprintf(fptr2, "%s", lvl6);
        fprintf(fptr2, "%s", lvl7);
        fprintf(fptr2, "%s", lvl8);
        fprintf(fptr2, "%s", lvl9);
        fprintf(fptr2, "%s", lvl10);
        fclose(fptr2);
    }

    free(t_empty);
    free(t_wall_n);
    free(t_wall_s);
    free(t_wall_e);
    free(t_wall_w);
    free(t_wall_ne);
    free(t_wall_nw);
    free(t_wall_se);
    free(t_wall_sw);
    free(t_block);

    cJSON_Delete(rootjson);
    free(out);

    return 0;
}