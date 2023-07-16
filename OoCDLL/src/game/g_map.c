#include "g_map.h"

#include "defs/d_common.h"
#include "defs/d_constants.h"

MapNode_t *mapnode_new(u32 key, Room_t *room) {
    if (room) {
        MapNode_t *node = (MapNode_t *) malloc(sizeof(MapNode_t));
        if (node) {
            node->key = key;
            node->room = room;
            node->north = NULLADDR;
            node->south = NULLADDR;
            node->east = NULLADDR;
            node->west = NULLADDR;
            return node;
        }
        else {
            errprintf("ERROR: no malloc space for new MapNode_t\n");
            return ERROR_MALLOC_NOSPACE;
        }
    }
    else {
        errprintf("ERROR: Room_t is null, can't make new MapNode_t\n");
        return ERROR_ISNULLADDR;
    }
}

MapNode_t *map_new(MapNode_t *root, u32 key, Room_t *room) {
    if (!root) {
        return mapnode_new(key, room);
    }
    else {
        errprintf("ERROR: map isn't null, can't make new map\n");
        return NULLADDR;
    }
}

MapNode_t *map_addnorth(MapNode_t *root, u32 key, Room_t *room) {
    if (!root) { // map is empty
        return map_new(root, key, room);
    }
    else if (!root->north) { // map isnt empty, and has no north
        MapNode_t *node = mapnode_new(key, room);
        if (node) {
            root->north = node;
            node->south = root;
            return root;
        } // no else, already covered by mapnode_new
    }
    else { // map isnt empty and has north
        return map_addnorth(root, key, room);
    }
}

MapNode_t *map_addsouth(MapNode_t *root, u32 key, Room_t *room) {
    if (!root) {
        return map_new(root, key, room);
    }
    else if (!root->south) {
        MapNode_t *node = mapnode_new(key, room);
        if (node) {
            root->south = node;
            node->north = root;
            return root;
        }
    }
    else {
        return map_addsouth(root, key, room);
    }
}

MapNode_t *map_addeast(MapNode_t *root, u32 key, Room_t *room) {
    if (!root) {
        return map_new(root, key, room);
    }
    else if (!root->east) {
        MapNode_t *node = mapnode_new(key, room);
        if (node) {
            root->east = node;
            node->west = root;
            return root;
        }
    }
    else {
        return map_addeast(root, key, room);
    }
}

MapNode_t *map_addwest(MapNode_t *root, u32 key, Room_t *room) {
    if (!root) {
        return map_new(root, key, room);
    }
    else if (!root->west) {
        MapNode_t *node = mapnode_new(key, room);
        if (node) {
            root->west = node;
            node->east = root;
            return root;
        }
    }
    else {
        return map_addwest(root, key, room);
    }
}

MapNode_t *map_addnorthbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey) {
    MapNode_t *leaf = map_searchbykey(root, tgtkey);
    if (leaf) {
        MapNode_t *newleaf = mapnode_new(key, room);
        if (newleaf) {
            if (leaf->north) {
                MapNode_t *const tmp = leaf->north;
                newleaf->south = leaf;
                leaf->north = newleaf;
                newleaf->north = tmp;
                newleaf->north->south = newleaf;
                return root;
            }
            else {
                leaf->north = newleaf;
                newleaf->south = leaf;
                return root;
            }
        }
        else {
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: can't add new MapNode_t, target node is null\n");
        return NULLADDR;
    }
}

MapNode_t *map_addsouthbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey) {
    MapNode_t *leaf = map_searchbykey(root, tgtkey);
    if (leaf) {
        MapNode_t *newleaf = mapnode_new(key, room);
        if (newleaf) {
            if (leaf->south) {
                MapNode_t *const tmp = leaf->south;
                newleaf->north = leaf;
                leaf->south = newleaf;
                newleaf->south = tmp;
                newleaf->south->north = newleaf;
                return root;
            }
            else {
                leaf->south = newleaf;
                newleaf->north = leaf;
                return root;
            }
        }
        else {
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: can't add new MapNode_t, target node is null\n");
        return NULLADDR;
    }
}

MapNode_t *map_addeastbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey) {
    MapNode_t *leaf = map_searchbykey(root, tgtkey);
    if (leaf) {
        MapNode_t *newleaf = mapnode_new(key, room);
        if (newleaf) {
            if (leaf->east) {
                MapNode_t *const tmp = leaf->east;
                newleaf->east = leaf;
                leaf->west = newleaf;
                newleaf->east = tmp;
                newleaf->east->west = newleaf;
                return root;
            }
            else {
                leaf->east = newleaf;
                newleaf->west = leaf;
                return root;
            }
        }
        else {
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: can't add new MapNode_t, target node is null\n");
        return NULLADDR;
    }
}

MapNode_t *map_addwestbykey(MapNode_t *root, u32 key, Room_t *room, const u32 tgtkey) {
    MapNode_t *leaf = map_searchbykey(root, tgtkey);
    if (leaf) {
        MapNode_t *newleaf = mapnode_new(key, room);
        if (newleaf) {
            if (leaf->west) {
                MapNode_t *const tmp = leaf->west;
                newleaf->west = leaf;
                leaf->east = newleaf;
                newleaf->west = tmp;
                newleaf->west->east = newleaf;
                return root;
            }
            else {
                leaf->west = newleaf;
                newleaf->east = leaf;
                return root;
            }
        }
        else {
            return NULLADDR;
        }
    }
    else {
        errprintf("ERROR: can't add new MapNode_t, target node is null\n");
        return NULLADDR;
    }
}

MapNode_t *map_searchbykey(MapNode_t *root, const u32 tgtkey) {
    if (!root || root->key == tgtkey) {
        return root;
    }
    else {
        // step 1: lock pointer to the root node down
        MapNode_t *const root_bak = root;

        // step 2: traverse north from root_bak (or in this case just root)
        root = map_searchnorthbykey(root, tgtkey);

        // step 3: tgt wasnt north of root; reset root to root_bak and traverse south

        root = root_bak;

        root = map_searchsouthbykey(root, tgtkey);

        IF_PTR_RETURN_PTR(root);

        // step 4: tgt wasn't north or south of root, reset root to root_bak and traverse east

        root = root_bak;

        root = map_searcheastbykey(root, tgtkey);

        IF_PTR_RETURN_PTR(root);

        // step 5: tgt wasnt north, south, or east of root, reset root to root_bak and traverse west

        root = root_bak;

        root = map_searchwestbykey(root, tgtkey);

        IF_PTR_RETURN_PTR(root);

        // step 6: tgt isn't anywhere in the direct cardinal directions from root; this is about to get complicated
        // start by going east until root->east == NULL

        root = root_bak;

        while (root->east) {
            root = root->east;
        }

        // step 7: make a new backup for this node thats farthest east
        // unlike before we need this one to change so it cant be const

        MapNode_t *branch = root;

        // step 8: search north on this branch

        root = map_searchnorthbykey(root, tgtkey);

        IF_PTR_RETURN_PTR(root);

        // step 9: tgt wasnt north of the east branch, search south

        root = branch;

        root = map_searchsouthbykey(root, tgtkey);

        IF_PTR_RETURN_PTR(root);

        // step 10: tgt wasnt north or south of east branch, 
        // so go west back towards root_bak until we get there
        // and search north then south

        while (branch->west && branch->west != root_bak) {
            branch = branch->west;
            root = branch;

            root = map_searchnorthbykey(root, tgtkey);

            IF_PTR_RETURN_PTR(root);

            root = branch;

            root = map_searchsouthbykey(root, tgtkey);

            IF_PTR_RETURN_PTR(root);
        }

        // step 11: tgt wasnt anywhere northeast or southeast of root
        // only place left that it could be is somewhere northwest of root or southwest of root
        // reset too back to root_bak and traverse west until root->west == NULL

        root = root_bak;
        branch = root_bak;

        while (root->west) {
            root = root->west;
        }

        branch = root;

        // step 12: search north of branch and then south of branch

        root = map_searchnorthbykey(root, tgtkey);

        IF_PTR_RETURN_PTR(root);

        root = branch;

        root = map_searchsouthbykey(root, tgtkey);

        IF_PTR_RETURN_PTR(root);

        // step 13: last chance to find tgt, go east towards root_bak and then search north and south

        while (branch->east && branch->east != root_bak) {
            branch = branch->east;
            root = branch;

            root = map_searchnorthbykey(root, tgtkey);

            IF_PTR_RETURN_PTR(root);

            root = branch;

            root = map_searchsouthbykey(root, tgtkey);

            IF_PTR_RETURN_PTR(root);
        }

        // step 14: tgt was nowhere to be found, we sweeped the map clean
        // return null and print an error message

        errprintf("ERROR: no MapNode_t found with key %d, returning null\n", tgtkey);
        return NULLADDR;

    }
}

MapNode_t *map_searchnorthbykey(MapNode_t *root, const u32 tgtkey) {
    if (!root || root->key == tgtkey) {
        return root;
    }
    else {
        return map_searchnorthbykey(root->north, tgtkey);
    }
}

MapNode_t *map_searchsouthbykey(MapNode_t *root, const u32 tgtkey) {
    if (!root || root->key == tgtkey) {
        return root;
    }
    else {
        return map_searchsouthbykey(root->south, tgtkey);
    }
}

MapNode_t *map_searcheastbykey(MapNode_t *root, const u32 tgtkey) {
    if (!root || root->key == tgtkey) {
        return root;
    }
    else {
        return map_searcheastbykey(root->east, tgtkey);
    }
}

MapNode_t *map_searchwestbykey(MapNode_t *root, const u32 tgtkey) {
    if (!root || root->key == tgtkey) {
        return root;
    }
    else {
        return map_searchwestbykey(root->east, tgtkey);
    }
}


Error_t mapnode_free(MapNode_t *leaf) {
    if (leaf) {
        Error_t e = room_free(leaf->room);
        free(leaf);
        return ERROR_NOERROR + e;
    }
}

Error_t map_free(MapNode_t *root) {
    
}

void map_freenorth(MapNode_t *branch) {
    if (branch) {
        MapNode_t *branch_bak = branch;

        while (branch->north) { // go as far north as we can
            branch = branch->north;
        }

        mapnode_free(branch);

        branch = branch_bak;

        map_freenorth(branch);


    }
}