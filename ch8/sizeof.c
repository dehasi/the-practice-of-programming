#include <stdio.h>

/* sizeof: display sizes of basic types*/
int main(int argc, char *argv[]) {
    printf("char %lu, short %lu, int %lu, long %lu,",
           sizeof(char), sizeof(short),
           sizeof(int), sizeof(long));

    printf(" float %lu, double %lu, void* %lu\n",
           sizeof(float), sizeof(double), sizeof(void *));
    return 0;
}
