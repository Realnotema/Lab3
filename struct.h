typedef struct Table {
    KeySpace1 *ks1;
    KeySpace2 *ks2;
    int msize;
    int csize;
} Table;

typedef struct Item {
    char *data;
    int release;
} Item;

typedef struct KeySpace1 {
    int key;
    int par;
    int busy;
    Item *info;
} KeySpace1;

typedef struct KeySpace2 {
    int key;
    int busy;
    Item *info;
} KeySpace2;
