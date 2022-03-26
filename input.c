#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "input.h"

int GetInt() {
        char *input = readline("=> ");
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
