#ifndef PROCESS_H
#define PROCESS_H

Table *InitTable (int count);
int DelTable (Table *table);
int AddElement (Table *table, int key1, int par, int key2, int rel, char *info);
int PrintTable (Table *table);
int FindKey1 (Table *table, int key);
int DeleteElement (Table *table, int key);
int DellWithChildren (Table *table, int key);
int Reorganize (Table *table);
Table *SearchVersion (Table *table, int rel);

#endif
