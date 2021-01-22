#include "csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>


enum {
    NOMEM = -2
}; /* out of memory signal */


static char *line = NULL; /* input chars */
static char *sline = NULL; /* line copy used by split */
static int maxline = 0; /* size of line[] and sline[] */
static char **field = NULL; /* field pointers */
static int maxfield = 0; /* size of field[] */
static int nfield = 0; /* number of fields in field[] */

static char fieldsep[] = ","; /* field separator characters */


static void reset();

static int endofline(FILE *fin, int c);

static int split();

static char *advquoted(char *p);

/* csvfield: returns a pointer to n-th field */
char *csvfield(int n) {
    if (n < 0 || n >= nfield) return NULL;

    return field[n];
}

/* csvnfield: returns number of fields */
int csvnfield() {
    return nfield;
}

/* csvgetline: get one e line, grow as needed */
/* sample input "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
char *csvgetline(FILE *fin) {
    if (line == NULL) { // allocate on the first call
        maxline = maxfield = 1;
        line = (char *) malloc(maxline);
        sline = (char *) malloc(maxline);
        field = (char **) malloc(maxfield * sizeof(field[0]));
        if (line == NULL || sline == NULL || field == NULL) {
            reset();
            return NULL; //out of memory
        }
    }

    int i, c;
    char *newl, *news;
    for (i = 0; (c = getc(fin)) != EOF && !endofline(fin, c); i++) {
        if (i > maxline - 1) { // grow the line
            maxline *= 2;
            newl = (char *) realloc(line, maxline);
            news = (char *) realloc(sline, maxline);
            if (newl == NULL || news == NULL) {
                reset();
                return NULL; // out of memory
            }
            line = newl;
            sline = news;
        }
        line[i] = c;
    }
    line[i] = '\0';
    if (split() == NOMEM) {
        reset();
        return NULL; // out of memory
    }
    return (c == EOF && i == 0) ? NULL : line;
}

/* endofline: check for and consume \r, \n, \r\n or EOF*/
static int endofline(FILE *fin, int c) {
    int eol = (c == '\r' || c == '\n');

    if (c == '\r') {
        c = getc(fin);
        if (c != '\n' && c != EOF)
            ungetc(c, fin); // read too far; put c back
    }
    return eol;
}

/* reset: sets variables back to starting values */
static void reset() {
    free(line); // free(NULL) permittet by ANSI C
    free(sline);
    free(field);
    line = NULL;
    sline = NULL;
    field = NULL;
    maxline = maxfield = 0;
}

/* split: splits a line into fields */
static int split() {
    char *p, **newf;
    char *sepp; // a pointer to a temporary separator character
    int sepc; // temporary separator character

    nfield = 0;
    if (line[0] == '\0') return 0;
    strcpy(sline, line);
    p = sline;

    do {
        if (nfield >= maxfield) {
            maxfield *= 2;
            newf = (char **) realloc(field, maxfield * sizeof(field[0]));
            if (newf == NULL) return NOMEM;
            field = newf;
        }
        if (*p == '"')
            sepp = advquoted(++p); // skip initial quote
        else
            sepp = p + strcspn(p, fieldsep);
        sepc = sepp[0];
        sepp[0] = '\0'; // terminate field
        field[nfield++] = p;
        p = sepp + 1;
    } while (sepc == ',');

    return nfield;
}

static char *advquoted(char *p) {
    int i, j;
    for (i = j = 0; p[j] != '\0'; i++, j++) {
        if (p[j] == '"' && p[++j] != '"') {
            // copy up to next separator or \0
            int k = strcspn(p + j, fieldsep);
            memmove(p + i, p + j, k);
            i += k;
            j += k;
            break;
        }
        p[i] = p[j];
    }
    p[i] = '\0';
    return p + j;
}
