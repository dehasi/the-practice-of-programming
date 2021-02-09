#include "eprintf.h"
#include <stdio.h>
#include <string.h>

typedef struct Symbol Symbol;
typedef struct Tree Tree;
typedef union Code Code;

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


union Code {
    void (*op)(void);  /* function if operator */
    int value;          /* value if number */
    Symbol *symbol;     /* Symbol entry if a variable */
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

enum {
    NCODE = 256,
    NSTACK = 256
};
Code code[NCODE];
int stack[NSTACK];
int stackp;
int pc; /* program counter */

/* pushop: push number, value is next word in code stream */
void pushop(void) {
    stack[stackp++] = code[pc++].value;
}

/* pushsymop: push a value of a variable */
void pushsymop(void) {
    stack[stackp++] = code[pc++].symbol->value;
}

/* addop: push sum of two stack expressions */
void addop(void) {
    int right = stack[--stackp];
    int left = stack[--stackp];
    stack[stackp++] = left + right;
}

/* divop: push division of two stack values */
void divop(void) {
    int right = stack[--stackp];
    int left = stack[--stackp];
    if (right == 0)
        eprintf("divide %d by zero", left);
    stack[stackp++] = left / right;
}


/* maxop: push max of two nodes on the stack  */
void maxop(void) {
    int right = stack[--stackp];
    int left = stack[--stackp];
    if (right == 0)
        eprintf("divide %d by zero", left);
    stack[stackp++] = left > right ? left : right;
}

/* assop: push right value to left */
void assop(void) {
    int right = stack[--stackp];
    stack[stackp++] = right;
    stack[stackp++] = right;
}

/* opttab: operator function table */
void (*opttab[])(void) = {
        pushop,     /* NUMBER */
        pushsymop,  /* VARIABLE */
        addop,      /* ADD */
        divop,      /* DIVIDE */
        maxop,      /* MAX */
        assop       /* ASSIGN */
};


/* generate: generate instructions by walking tree */
int generate(int codep, Tree *t) {
    switch (t->op) {
        case NUMBER:
            code[codep++].op = pushop;
            code[codep++].value = t->value;
            return codep;
        case VARIABLE:
            code[codep++].op = pushsymop;
            code[codep++].symbol = t->symbol;
            return codep;
        case ADD:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = addop;
            return codep;
        case DIVIDE:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = divop;
            return codep;
        case MAX:
            codep = generate(codep, t->left);
            codep = generate(codep, t->right);
            code[codep++].op = maxop;
            return codep;
        case ASSIGN: // ??
            codep = generate(codep, t->right);
            code[codep++].op = assop;
            return codep;
        default:
            eprintf("unknown operator %d", t->op);
            return -1;
    }
}

/* eval: versin 3: evaluate expression from generated code */
int eval(Tree *t) {
    pc = generate(0, t);
    code[pc].op = NULL;

    stackp = 0;
    pc = 0;
    while (code[pc].op != NULL)
        (*code[pc++].op)();
    return stack[0];
}

int main(int argc, char *argv[]) {
    setprogname("grep");

    return 0;
}
