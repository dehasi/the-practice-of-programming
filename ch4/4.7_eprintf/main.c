#include "eprintf.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

    setprogname("markov");
    char *path = "/path/to/file";
    FILE *f = fopen(path, "r");
    if (f == NULL)
        eprintf("can't open %s:", path);
    return 0;
}
