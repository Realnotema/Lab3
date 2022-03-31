#include "struct.h"
#include "input.h"
#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

int Dialog(const char *options[], int CountOptions) {
        int choose = 0;
        for (int i = 0; i < CountOptions; i++)
                puts(options[i]);
        char *errmess = "";
        do {
                puts(errmess);
                do {
                        choose = GetInt();
                } while (choose > CountOptions || choose < 0);
                if (choose < 0 || choose > CountOptions)
                        errmess = "Incorrect input. Try again";
        } while (choose < 0 || choose > CountOptions);
        return choose;
}

int AddMenu (Table *table) {
        int key[2];
        int par;
        char *mess[] = {"Enter first key:", "Enter second key ", "Enter parent of first element (0 if no parent)", "Enter string: "};
        for (int i = 0; i < 2; i++) {
                puts(mess[i]);
                key[i] = GetInt();
                if (i == 0) {
                        puts(mess[2]);
                        do {
                                par = GetInt();
                        } while (FindKey1(table, par) == 1 && par != 0);
                }
        }
        puts(mess[3]);
        char *string = readline("");
        AddElement(table, key[0], par, key[1], string);
        return 0;
}

int EditMenu (int choose, Table *table) {
        int flag = 0;   
        char *mess[] = {"Enter key of parent:", "Reorganized succesfully!", "Enter realise:"};
        switch (choose) {
                case 1:
                        puts(mess[0]);
                        int key = GetInt();
                        DellWithChildren(table, key);
                        break;
                case 2:
                        flag = Reorganize (table);
                        if (flag == 0)
                                puts(mess[1]);
                        break;
                case 3:
                        puts(mess[2]);
                        int rel = GetInt();
                        SearchVersion(table, rel);
                        break;
                case 4:
                        return 1;
        }
        return 0;
}


int Menu(int choose, Table *table) {
        char *mess = "Enter key from first key space to delete:";
        const char *options[] = {"1. Delete relatives of element", "2. Reorganize the table", "3. Search by version of element", "4. Quit"};
        int flag;
        switch(choose) {
                case 1:
                        AddMenu(table);
                        break;
                case 2:
                        PrintTable(table);
                        break;
                case 3:
                        puts(mess);
                        int n = GetInt();
                        DeleteElement(table, n);
                        break;
                case 4:
                        do {
                                flag = EditMenu(Dialog(options, 4), table);
                        } while (flag == 0);
                        break;
                case 5:
                        return 1;
        }
        return 0;
}

int main() {
        int flag;
        const char *options[] = {"1. Add element", "2. Print table", "3. Delete element", "4. Edit table", "5. Quit"};
        char *mess = "Enter count of keys:";
        puts(mess);
        int count = GetInt();
        Table *table = InitTable(count);
        do {
                flag = Menu(Dialog(options, 5), table);
        } while (flag == 0);
        DelTable(table);
        return 0;
}
