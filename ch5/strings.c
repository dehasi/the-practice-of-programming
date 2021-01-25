#include "../ch4/4.7_eprintf/eprintf.h"
#include <stdio.h>
#include <ctype.h>

enum {
    BUF_SIZE = 100,
    MIN_LEN = 6
};

/* strings: extracts printable strings from stream */
void strings(char *name, FILE *fin) {
    int c, i;
    char buf[BUF_SIZE];

    do {
        for (i = 0; (c = getc(fin)) != EOF;) {
            if (!isprint(c))
                break;
            buf[i++] = c;
            if (i >= BUF_SIZE)
                break;
        }
        if (i >= MIN_LEN)
            printf("%s:%.*s\n", name, i, buf);
    } while (c != EOF);
}

/* strings main: find printable string in files */
int main(int argc, char *argv[]) {

    setprogname("strings");

    if (argc == 1)
        eprintf("usage: strings filenemes");
    else {
        FILE *fin;
        for (int i = 1; i < argc; i++) {
            if ((fin = fopen(argv[i], "rb")) == NULL)
                weprintf("can't open %s:", argv[i]);
            else{
                strings(argv[i], fin);
                fclose(fin);
            }
        }
    }
    return 0;
}
