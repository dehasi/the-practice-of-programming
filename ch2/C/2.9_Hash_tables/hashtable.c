#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
    Nameval *next;
};

const int NHASH = 31;

Nameval *symtab[NHASH];

enum {MULTIPLIER = 31};

unsigned int hash(char *str)
{
    unsigned int h = 0;
    unsigned char *p;
    for(p = (unsigned char*) str; *p != '\0'; p++)
        h = MULTIPLIER * h + *p;
    return h % NHASH;
}

Nameval *lookup(char *name, int create, int value)
{
    int h = hash(name);
    for(Nameval *sym = symtab[h]; sym != NULL; sym = sym->next)
        if(strcmp(name, sym->name) == 0)
            return sym;
    if (create) {
        Nameval *sym = (Nameval*) malloc(sizeof(Nameval));
        sym -> name = name;
        sym -> value = value;
        sym->next = symtab[h];
        symtab[h] = sym;
    }
}
