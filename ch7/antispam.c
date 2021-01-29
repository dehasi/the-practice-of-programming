#include "../ch4/4.7_eprintf/eprintf.h"
#include <stdio.h>
#include <libc.h>

enum {
    NPAT = 6,
    NSTART = 42
};

char *pat[NPAT] = {"AAA", "BBB", "CCC", "DDD", "CDC", "ABD"}; /* spam patterns */
unsigned int patlen[NPAT]; /* length of a pattern */
int starting[UCHAR_MAX + 1][NSTART]; /* pats starting with char */
int nstarting[UCHAR_MAX + 1]; /* number of such patterns */

/* isspam: test mesg for occurrence of any pat*/
int isspam(char *mesg) {
    char c;
    for (int j = 0; (c = mesg[j]) != '\0'; j++) {
        int n = nstarting[c];
        for (int i = 0; i < n; i++) {
            int k = starting[c][i];
            if (memcmp(mesg + j, pat[k], patlen[k]) == 0) {
                printf("spam: match for '%s'\n", pat[k]);
                return 1;
            }
        }
    }
    return 0;
}

/* fill: fills arrays based on pat[] */
void fill() {
    for (int i = 0; i < NPAT; ++i) {
        unsigned char c = pat[i][0];
        if (nstarting[c] >= NSTART) {
            eprintf("too many patterns (>=%d) begin '%c'", NSTART, c);
        }
        starting[c][nstarting[c]++] = i;
        patlen[i] = strlen(pat[i]);
    }
}

/* getbits: returns n bits from position p */
/* bits are numbered from 0 (least significant) up */
unsigned int getbits(unsigned int x, int p, int n) {
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

int main(int argc, char *argv[]) {
    setprogname("antispam");

    if (argc == 1) eprintf("usage: antispam textword");

    fill();
    for (int i = 1; i < argc; i++)
        printf("message[%d] isspam = %d\n", i, isspam(argv[i]));

    return 0;
}
