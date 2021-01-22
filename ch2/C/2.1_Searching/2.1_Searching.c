#include <stdio.h>
#include <string.h>


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

int lookup(char *word, char *array[]) {
    for (int i = 0; array[i] != NULL; i++) {
        if (strcmp(word, array[i]) == 0) return i;
    }
    return -1;
}

int main() {
   printf("result = %i\n", lookup("just", flab));
   return 0;
}