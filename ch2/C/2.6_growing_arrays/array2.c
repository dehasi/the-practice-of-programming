#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
};

struct NVTab {
    int nval;
    int gaps;
    int max;
    Nameval *nameval;
} nvtab;

enum { NVINIT=1, NVGROW=2 };

int addname(Nameval newname)
{
    Nameval *nvp;

    if (nvtab.nameval == NULL) {
         nvtab.nameval = (Nameval*) malloc(NVINIT * sizeof(Nameval));
         if (nvtab.nameval == NULL) return -1;
         nvtab.max = NVINIT;
         nvtab.nval = 0;
         nvtab.gaps = 0;
    } else if (nvtab.nval >=nvtab.max) {
        nvp = realloc(nvtab.nameval, (NVGROW * nvtab.max) * sizeof(Nameval));
        if (nvp == NULL) return -1;
        nvtab.max *= NVGROW;
        nvtab.nameval = nvp;
    }
    nvtab.nameval[nvtab.nval] = newname;
    return nvtab.nval++;
}

int delname(char* name) {

    for(int i = 0; i < nvtab.nval; ++i)
         if (strcmp(nvtab.nameval[i].name, name) == 0) {
            free(&nvtab.nameval[i]);
            nvtab.nameval[i] = NULL;
            nvtab.gaps++;
            return 1;
         }
    return 0;
}


void printNameval(Nameval nameval) {
    printf("%s %d\n", nameval.name, nameval.value);
}

int main(int argc, char *argv[]) {
    Nameval n1, n2, n3;
    n1.value = 1;
    n1.name = "one";

    n2.value = 2;
    n2.name = "two";

    n3.value = 3;
    n3.name = "three";

    addname(n2);
    addname(n3);
    addname(n1);

    for(int i = 0; i < nvtab.nval; ++i) {
        printNameval(nvtab.nameval[i]);
    }

    delname("three");

    for(int i = 0; i < nvtab.nval; ++i) {
        if (nvtab.nameval[i] != NULL)
            printNameval(nvtab.nameval[i]);
    }
    return 0;
}
