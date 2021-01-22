#include <stdio.h>
#include <cheat.h>

CHEAT_DECLARE(
    typedef struct Nameval Nameval;
    struct Nameval {
        char *name;
        int value;
        Nameval *left; /* lesser */
        Nameval *right; /* greater */
    };
    extern Nameval* newintem(char *name, int value);
    extern Nameval *insert(Nameval *treep, Nameval *newp);
    extern Nameval *lookup(Nameval *treep, char *name);
    extern Nameval *nrlookup(Nameval *treep, char *name);
)

CHEAT_TEST(inserts,
    Nameval *result = insert(newintem("1",1), newintem("2",2));

    cheat_assert(result->left != NULL);
    cheat_assert(result->right == NULL);
)


CHEAT_TEST(lookup,
    Nameval* treep = NULL;
    treep = insert(treep, newintem("1",1));
    treep = insert(treep, newintem("2",2));
    treep = insert(treep, newintem("3",3));

    Nameval *result = lookup(treep, "2");

    cheat_assert(result->value == 2);
)

CHEAT_TEST(nrlookup,
    Nameval* treep = NULL;
    treep = insert(treep, newintem("1",1));
    treep = insert(treep, newintem("2",2));
    treep = insert(treep, newintem("3",3));

    Nameval *result = nrlookup(treep, "2");

    cheat_assert(result->value == 2);
)
