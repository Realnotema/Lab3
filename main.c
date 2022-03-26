#include "struct.h"
#include "input.h"
#include "process.h"
#include <stdlib.h>
#include <stdio.h>

int Dialog(const char *options[], int CountOptions) {
        int choose = 0;
        for (int i = 0; i < CountOptions; i++)
                puts(options[i]);
        char *errmess = "";
        do {
                puts(errmess);
                choose = GetInt();
                if (choose < 0 || choose > CountOptions)
                        errmess = "Incorrect input. Try again";
        } while (choose < 0 || choose > CountOptions);
        return choose;
}

int Menu(int choose, Table *table) {
        switch(choose) {
                case 1:
                        printf("You choose 1. Add element\n");
                        break;
                case 2:
                        printf("You choose 2. Edit element\n");
                        break;
                case 3:
                        printf("You choose 3. Delete element\n");
                        break;
                case 4:
                        break;
                default:
                        exit (-1);
        }
}

int main() {
        const char *options[] = {"1. Add element", "2. Edit element", "3. Delete element", "4. Quit"};
        char *mess = "Enter count of keys:";
        puts(mess);
        int count = GetInt();
        Table *table = InitTable(count);
        do {
                Menu(Dialog(options, 4), table);
        } while (Dialog(options, 4) != 4);
        DelTable(table);
        return 0;
}
