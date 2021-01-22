#include "csv.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

    char *line;
    while ((line = csvgetline(stdin)) != NULL) {
        printf("line = '%s'\n", line);
        for (int i = 0; i < csvnfield(); i++)
            printf("field[%d] = '%s'\n", i, csvfield(i));
    }
    return 0;
}
