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
                if (table->ks1[i].busy != 0) free(table->ks1[i].info);
        }
        free(table->ks1);
        free(table->ks2);
        free(table);
        return 0;
}
