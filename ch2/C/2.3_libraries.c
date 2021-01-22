#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scmp(const void *p1, const void *p2) {
    char *v1, *v2;

    v1 = (char*) p1;
    v2 = (char*) p2;

    return -1 * strcmp(v1, v2);
}

const int N = 4;

char *str[N] = {
    "quite",
    "just",
    "actually",
    "really"
};

const int INT_N = 7;
int ints[INT_N] = {6,5,4,3,2,1,0};

int icmp(const void *p1, const void *p2) {
    int v1, v2;
    v1 = *(int *) p1;
    v2 = *(int *) p2;

    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
}


typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
};

Nameval htmlchars[] = {
    "AElig", 0x00c6,
    "Aacute", 0x00c1,
    "Acirc", 0x00c2,
    /* ... */
    "zeta", 0x03b6
};

char *flab[] = {
    "actually",
    "just",
    "quite",
    "really",
    NULL
};

int nvcmp(const void *p1, const void *p2)
{
    const Nameval *v1, *v2;
    v1 = (Nameval*) p1;
    v2 = (Nameval*) p2;

    return strcmp(v1->name, v2->name);
}

int lookup(char *name, Nameval tab[], int ntab)
{
    Nameval key, *np;

    key.name = name;
    key.value = 0;

    np = (Nameval *) bsearch(&key, tab, ntab, sizeof(tab[0]), nvcmp);
    if (np == NULL)
        return -1;
    else
        return np-tab;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < N; printf("%s ", str[i++])); printf("\n");

    qsort(str, N, sizeof(str[0]), scmp);

    for (int i = 0; i < N; printf("%s ", str[i++])); printf("\n");

    //
    for (int i = 0; i < INT_N; printf("%d ", ints[i++])); printf("\n");

    qsort(ints, INT_N, sizeof(ints[0]), icmp);

    for (int i = 0; i < INT_N; printf("%d ", ints[i++])); printf("\n");

    //
    printf("result = %i\n", lookup("AElig", htmlchars, 4));
    printf("result = %i\n", lookup("Aacute", htmlchars, 4));
    printf("result = %i\n", lookup("Acirc", htmlchars, 4));
    printf("result = %i\n", lookup("zeta", htmlchars, 4));
    return 0;
}
