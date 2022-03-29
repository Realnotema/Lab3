#include "struct.h"
#include <stdlib.h>
#include <stdio.h>

Table *InitTable (int count) {
        Table *table = (Table *) malloc(sizeof(Table));
        table->msize = count;
        table->csize = 0;
        table->ks1 = (KeySpace1 *) malloc(count*sizeof(KeySpace1));
        for (int i = 0; i < count; i++) table->ks1[i].busy = 0;
        table->ks2 = (KeySpace2 *) malloc(count*sizeof(KeySpace2));
        for (int i = 0; i < count; i++) table->ks2[i].busy = 0;
        return table;
}

int DelTable (Table *table) {
        for (int i = 0; i < table->msize; i++) {
                if (table->ks1[i].busy != 0) {
                        free(table->ks1[i].info);
                }
        }
        free(table->ks1);
        free(table->ks2);
        free(table);
        return 0;
}

int hash (int *hash_position) {
        if (*hash_position == *hash_position % 10) return 1;
        *hash_position %= 10;
        return 0;
}

int AddElement (Table *table, int key1, int par, int key2, char *info) {
        int pos1 = key1 - 1, pos2 = key2 - 1, flag = 0;
        if (pos1 < 0) pos1 = 0;
        if (pos2 < 0) pos2 = 0;
        if (pos1 >= table->msize) {
                pos1 = 0;
                while (table->ks1[pos1].busy == 1)
                        pos1++;
        }
        if (pos1 < table->msize && table->ks1[pos1].busy == 1) {
                while (pos1 != table->msize - 1 && table->ks1[pos1].busy == 1) {
                        pos1++;
                }
                if (table->ks1[pos1].busy == 1)
                        flag++;
                if (flag == 1) {
                        for (int i = 0; i <  table->msize; i++) {
                                if (table->ks1[i].busy == 0) {
                                        pos1 = i;
                                }
                        }
                }
        }
        if (flag == 1) {
                char *errmess = "Memory error!";
                puts(errmess);
                return 1;
        }
        flag = 0;
        if (pos2 >= table->msize) {
                pos2 = 0;
                while (table->ks2[pos2].busy == 1)
                        pos2++;
        }
        while (pos2 < table->msize && table->ks2[pos2].busy == 1) {
                flag = hash(&pos2);
                for (int i = 0; i < table->msize && table->ks2[pos2].busy == 1; i++)
                        pos2 = (pos2 + i) % table->msize;
                if (flag == 1)
                        break;
        }
        table->csize++;
        table->ks1[pos1].key = key1;
        table->ks1[pos1].busy = 1;
        table->ks1[pos1].info = info;
        table->ks2[pos1].realise  = 0;
        table->ks1[pos1].par = par;
        table->ks2[pos2].key = key2;
        table->ks2[pos2].busy = 1;
        table->ks2[pos2].info = table->ks1[pos1].info;
        return 0;
}

int FindKey1 (Table *table, int key) {
        char *errmess = "No match key!\nTry Again";
        if (key == 0) return 0;
        for (int i = 0; i < table->msize; i++) {
                if (table->ks1[i].busy == 1 && table->ks1[i].key == key) {
                        return 0;
                }
        }
        puts(errmess);
        return 1;
}

int FindPos2 (Table *table, int pos1) {
        int pos2 = 0;
        for (int i = 0; i < table->msize; i++) {
                if ((table->ks1[i].busy == 1 || table->ks2[i].busy == 1) && table->ks2[i].info == table->ks1[pos1].info) {
                        pos2 = i;
                        break;
                }
        }
        return pos2;
}

int FindPos1 (Table *table, int key) {
        int pos1 = 0;
        for (int i = 0; i < table->msize; i++) {
                if (table->ks1[i].busy == 1 && table->ks1[i].key == key) {
                        pos1 = i;
                        return pos1;
                }
        }
        return pos1;
}

int DeleteElement (Table *table, int key) {
        int pos1 = FindPos1(table, key);
        table->ks1[pos1].busy = 0;
        int pos2 = FindPos2(table, pos1);
        table->ks2[pos2].busy = 0;
        table->csize--;
        return 0;
}

int PrintTable (Table *table) {
        for (int i = 0; i <= table->csize; i++) {
                if (table->ks1[i].busy == 1) {
                        int pos2 = FindPos2(table, i);
                        printf("(%d,%d)\t%s\n", table->ks1[i].key, table->ks2[pos2].key, table->ks1[i].info);
                }
        }
        return 0;
}

int FindParents (Table *table, int key) {
        for (int i = 0; i < table->msize; i++) {
                if (table->ks1[i].busy == 1 && table->ks1[i].par == key)
                        return table->ks1[i].key;
        }
        return -1;
}

int DellWithChildren (Table *table, int key) {
        if (key == -1) return 0;
        int pos1 = FindPos1(table, key);
        table->ks1[pos1].busy = 0;
        int pos2 = FindPos2(table, pos1);
        table->ks2[pos2].busy = 0;
        DellWithChildren(table, FindParents(table, key));
}
