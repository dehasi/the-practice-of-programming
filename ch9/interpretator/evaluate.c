#include "eprintf.h"
#include <stdio.h>
#include <string.h>

typedef struct Symbol Symbol;
typedef struct Tree Tree;

struct Symbol {
    int value;
    char *name;
};

struct Tree {
    int op;          /* operation code */
    int value;       /* value if number */
    Symbol *symbol;  /* Symbol entry if variable */
    Tree *left;
    Tree *right;
};

enum { /* operation code, Tree.op*/
    NUMBER,
    VARIABLE,
    ADD,
    DIVIDE,
    MAX,
    ASSIGN
    /* ... */
};

/* eval: version 1: evaluate tree expression */
int eval(Tree *t) {
    int left, right;
    switch (t->op) {
        case NUMBER:
            return t->value;
        case VARIABLE:
            return t->symbol->value;
        case ADD:
            return eval(t->left) + eval(t->right);
        case DIVIDE:
            left = eval(t->left);
            right = eval(t->right);
            if (right == 0)
                eprintf("divide %d by zero", left);
            return left / right;
        case MAX:
            left = eval(t->left);
            right = eval(t->right);
            return left > right ? left : right;
        case ASSIGN:
            t->left->symbol->value = eval(t->right);
            return t->left->symbol->value;
        default:
            eprintf("unknown operator %d", t->op);
            return -1;
    }
}

/* pushop: retuns a value */
int pushop(Tree *t) {
    return t->value;
}

/* pushsymop: retuns a value of a variable */
int pushsymop(Tree *t) {
    return t->symbol->value;
}

/* addop: return sum of two tree expressions */
int addop(Tree *t) {
    return eval(t->left) + eval(t->right);
}

/* divop: return division of two tree expressions */
int divop(Tree *t) {
    int left = eval(t->left);
    int right = eval(t->right);
    if (right == 0)
        eprintf("divide %d by zero", left);
    return left / right;
}


/* maxop: retuns max of left and right nodes  */
int maxop(Tree *t) {
    int left = eval(t->left);
    int right = eval(t->right);
    return left > right ? left : right;
}

/* assop: assign right value to left */
int assop(Tree *t) {
    t->left->symbol->value = eval(t->right);
    return t->left->symbol->value;
}

/* opttab: operator function table */
int (*opttab[])(Tree *) = {
        pushop,     /* NUMBER */
        pushsymop,  /* VARIABLE */
        addop,      /* ADD */
        divop,      /* DIVIDE */
        maxop,      /* MAX */
        assop       /* ASSIGN */
};

/* eval: version 2: evaluate tree from operator table*/
int eval2(Tree *t) {
    return (*opttab[t->op])(t);
}

int main(int argc, char *argv[]) {
    setprogname("grep");

    return 0;
}
