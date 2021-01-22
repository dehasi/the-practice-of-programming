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

Nameval* newintem(char *name, int value)
{
    Nameval *newp;

    newp = (Nameval*) malloc(sizeof(Nameval));
    newp->name = name;
    newp->value = value;
    newp->next = NULL;
    return newp;
}

Nameval* addfrond(Nameval *listp, Nameval *newp) {
    newp->next = listp;
    return newp;
}

Nameval* addend(Nameval *listp, Nameval *newp)
{
    if (listp == NULL) return newp;
    Nameval *p;
    for (p = listp; p->next != NULL; p = p->next)
        ;

    p->next = newp;
    return listp;
}


Nameval* lookup(Nameval* listp, char *name)
{
    for( ; listp != NULL; listp = listp->next)
        if( strcmp(name, listp->name) == 0)
            return listp;
    return NULL;
}

void apply(Nameval *listp, void (*fn)(Nameval*, void*), void* arg)
{
    for( ; listp != NULL; listp = listp->next)
        (*fn)(listp, arg);
}

void printnv(Nameval* p, void* arg) {
    char *fmt;

    fmt = (char*) arg;
    printf(fmt, p->name, p->value);
}

void icounter(Nameval *p, void* arg)
{
    int *ip;

    ip = (int *) arg;
    (*ip)++;
}

void freeall(Nameval *listp)
{
    Nameval *next;
    for( ; listp != NULL; listp = next) {
        next = listp -> next;
        free(listp);
    }
}

Nameval *delitem(Nameval *listp, char *name)
{
    Nameval *p, *prev;
    prev = NULL;
    for(p = listp; p != NULL; p = p->next) {
         if( strcmp(name, listp->name) == 0) {
            if (prev == NULL)
                listp = p->next;
            else
                prev->next = p->next;
            free(p);
            return listp;
         }
         prev = p;
    }
    printf("delitem: %s not in list", name); //eprintf
    return NULL;
}

int main(int argc, char *argv[]) {
    Nameval* nvlist = newintem("aaaa", 111);
//    Nameval* nvlist = NULL;
    nvlist = addend(nvlist, newintem("bbb",222));


    apply(nvlist, printnv, "%s %d\n");
    int n = 0;
    apply(nvlist, icounter, &n);
    printf("n = %d\n", n);
    apply(lookup(nvlist, "bbb"), printnv, "%s %d\n");
    freeall(nvlist);
    return 0;
}
