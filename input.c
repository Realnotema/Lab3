#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "input.h"

int get_int() {
        char *input = readline("");
        if (input == NULL) {
                free(input);
                return 0;
        }
        if (atoi(input) == 0){
                free(input);
                return 0;
        }
        int output = atoi(input);
        free(input);
				return output;
}

char *enter() {
        char *str = readline("=>  ");
        char *temp = str;
        int n = 0;
        while (*temp != '\0') {
                if (*temp == '/') {
                        n++;
                }
                temp++;
        }
        if (n != 2) {
                return NULL;
        }
        return str;
}
