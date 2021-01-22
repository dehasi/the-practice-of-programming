#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

enum {
    NPREF  = 2,    /* number of prefix words */
    NHASH  = 4093, /* size of state hash table array */
    MAXGEN = 10000 /* maximum words generated */
};

char NONWORD[] = "\n"; /* cannot appear as a real word */

typedef struct State State;
typedef struct Suffix Suffix;

struct State { /* prefix + suffix list */
    char *pref[NPREF]; /* prefix words */
    Suffix *suf;       /* list of suffixes */
    State *next;       /* next in hash table */
};

struct Suffix {
    char   *word; /* suffix */
    Suffix *next; /* next is list of suffixes */
};

State *statetab[NHASH]; /* hash table of states */

enum {MULTIPLIER = 31};
/* hash: compute hash value for array of NPREF strings */
unsigned int hash(char *s[NPREF])
{
    unsigned int h=0;
    for(int i = 0; i < NPREF; i++)
        for(unsigned char* p = (unsigned char*) s[i]; *p != '\0'; p++)
            h = MULTIPLIER * h + *p;
    return h % NHASH;
}

/* lookup: search for prefix; create if requested. */
/* returns a pointer if present or created NULL if not. */
/* creation doesn't strdup so strings mustn't change later. */
State* lookup(char *prefix[NPREF], int create)
{
    int h = hash(prefix);
    State* sp = NULL;
    for(sp = statetab[h]; sp != NULL; sp = sp->next) {
        int i;
        for(i = 0; i < NPREF; i++)
            if (strcmp(prefix[i], sp->pref[i]) != 0)
                break;
        if(i == NPREF) /* found */
            return sp;
    }
    if (create) {
        sp = (State*) malloc(sizeof(State));
        for(int i = 0; i < NPREF; i++)
             sp->pref[i] = strdup(prefix[i]);
        sp->suf = NULL;
        sp->next = statetab[h];
        statetab[h] = sp;
    }
    return sp;
}

/* addsuffix: add to state. suffix must not change later */
void addsuffix(State *sp, char *suffix)
{
    Suffix* suf = (Suffix*) malloc(sizeof(Suffix));
    suf->word = suffix;
    suf->next = sp->suf;
    sp->suf = suf;
}

/* add: add word to suffix list, update prefix*/
void add(char *prefix[NPREF], char *suffix)
{
    State* sp = lookup(prefix, 1); /* create if not found */
    addsuffix(sp, suffix);
    /* move the words down the prefix */
    memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));
    prefix[NPREF-1] = suffix;
}

/* build: read input, build prefix table */
void build(char *prefix[NPREF], FILE *f)
{
    char buf[100], fmt[10];

    /* create a format string; %s could overflow buf */
    sprintf(fmt, "%%%lus", sizeof(buf)-1);
    while(fscanf(f, fmt, buf) != EOF)
        add(prefix, strdup(buf)); //esrtdup
}

/* generate: produce output, one word per line */
void generate(int nwords)
{
    State *sp;
    Suffix *suf;
    char *prefix[NPREF];

    for(int i=0; i< NPREF; i++) /* reset initial prefix */
        prefix[i] = NONWORD;

    for(int i=0; i< nwords; i++) {
         sp = lookup(prefix, 0);
         int nmatch = 0;
         char *w;
         for(suf = sp->suf; suf != NULL; suf = suf->next) {
            if(rand() % ++nmatch == 0) /* prob = 1/nmatch */
                w = suf->word;
         }
         if(strcmp(w, NONWORD) == 0)
            break;
         printf("%s\n",w);

         memmove(prefix, prefix+1, (NPREF-1)*sizeof(prefix[0]));

         prefix[NPREF-1] = w;
    }
}

int main(int argc, char *argv[])
{
    int nwords = MAXGEN;
    char *prefix[NPREF]; /* current input prefix */

    for(int i=0; i< NPREF; i++) /* set up initial prefix */
        prefix[i] = NONWORD;

    build(prefix, stdin);
    add(prefix, NONWORD);

    generate(nwords);
    return 0;
}
