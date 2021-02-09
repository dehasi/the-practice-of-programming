#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *name = NULL;

char *progname();

void setprogname(const char *str);


/* weprintf: print warning message */
void weprintf(const char *fmt, ...) {
    va_list args;

    fflush(stdout);
    if (progname() != NULL)
        fprintf(stderr, "%s: ", progname());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
        fprintf(stderr, " %s", strerror(errno));
    fprintf(stderr, "\n");
}

/* eprintf: print error message and exit */
void eprintf(char *fmt, ...) {
    va_list args;

    fflush(stdout);
    if (progname() != NULL)
        fprintf(stderr, "%s: ", progname());

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    if (fmt[0] != '\0' && fmt[strlen(fmt) - 1] == ':')
        fprintf(stderr, " %s", strerror(errno));
    fprintf(stderr, "\n");
    exit(2); /* conventional value for failed execution */
}

/* emalloc: malloc and report if error */
void *emalloc(size_t n) {
    void *p = malloc(n);
    if (p == NULL)
        eprintf("malloc of %u byted failed:", n);
    return p;
}

/* erealloc: realloc and report if error */
void *erealloc(void *ptr, size_t n) {
    void *newp = realloc(ptr, n);
    if (newp == NULL)
        eprintf("realloc %p of %u byted failed:", ptr, n);
    return newp;
}


/* estrdup: duplicates a string, reports if error */
char *estrdup(const char *s) {
    char *t = (char *) malloc(strlen(s) + 1);
    if (t == NULL)
        eprintf("estrdup(\"%.20s\") failed:", s);
    strcpy(t, s);
    return t;
}

/* setprogname: sets stored name of program */
void setprogname(const char *str) {
    name = estrdup(str);
}

/* progname: returns stored name of program */
char *progname() {
    return name;
}
