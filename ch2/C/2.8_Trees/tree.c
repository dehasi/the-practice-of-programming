#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>


typedef struct Nameval Nameval;
struct Nameval {
    char *name;
    int value;
    Nameval *left; /* lesser */
    Nameval *right; /* greater */
};

Nameval* newintem(char *name, int value)
{
    Nameval *newp;

    newp = (Nameval*) malloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->left = NULL;
    newp->right = NULL;
    return newp;
}

Nameval *insert(Nameval *treep, Nameval *newp)
{
    if (treep == NULL)
        return newp;

    int cmp = strcmp(treep->name, newp->name);
    if (cmp == 0)
        printf("insert: duplicate entry %s ignored", newp->name);
    else if (cmp < 0)
        treep->left = insert(treep->left, newp);
    else
        treep->right = insert(treep->right, newp);
    return treep;
}

Nameval *lookup(Nameval *treep, char *name)
{
    if (treep == NULL)
        return NULL;

    int cmp = strcmp(treep->name, name);
    if (cmp == 0)
        return treep;
    else if (cmp < 0)
        return lookup(treep->left, name);
    else
        return lookup(treep->right, name);
}

Nameval *nrlookup(Nameval *treep, char *name)
{
    while (treep != NULL) {
    int cmp = strcmp(treep->name, name);
    if (cmp == 0)
           return treep;
       else if (cmp < 0)
           treep = lookup(treep->left, name);
       else
           treep = lookup(treep->right, name);
    }
    return NULL;
}

void applyinorder(Nameval *treep, void (*fn)(Nameval*, void*), void* arg)
{
    if (treep == NULL) return;

    applyinorder(treep->left, fn, arg);
    (*fn)(treep, arg);
    applyinorder(treep->right, fn, arg);
}


void applypostorder(Nameval *treep, void (*fn)(Nameval*, void*), void* arg)
{
    if (treep == NULL) return;

    applypostorder(treep->left, fn, arg);
    applypostorder(treep->right, fn, arg);
    (*fn)(treep, arg);
}
