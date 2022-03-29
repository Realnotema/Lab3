#ifndef STRUCT_H
#define STRUCT_H

/*typedef struct Item {
        char *data;
} Item;*/

typedef struct KeySpace1 {
        int key;
        int par;
        int busy;
        char *info;
} KeySpace1;

typedef struct KeySpace2 {
        int key;
        int busy;
        int realise;
        char *info;
} KeySpace2;

typedef struct Table {
        KeySpace1 *ks1;
        KeySpace2 *ks2;
        int msize;
        int csize;
} Table;

#endif
