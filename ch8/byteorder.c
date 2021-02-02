#include <stdio.h>

/* byteorder: display bytes of a long */
int main(int argc, char *argv[]) {
    /* 11 22 33 44 => big-endian */
    /* 44 33 22 11 => little-endian */
    unsigned long x = 0x1122334455667788UL;
    unsigned char *p = (unsigned char *) &x;

    for (int i = 0; i < sizeof(long); ++i)
        printf("%x ", *p++);
    printf("\n");
    return 0;
}
