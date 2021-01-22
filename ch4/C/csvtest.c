#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>

char buf[200]; /* input line buffer */
char *field[20]; /* fields */

/* unquote: remove leading and trailing quote*/
char *unquote(char *str) {
    if (str[0] == '"') {
        if (str[strlen(str) - 1] == '"')
            str[strlen(str) - 1] = '\0';
        str++;
    }
    return str;
}

/* csvgetline: read and parse line, return field count */
/* sample input "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
int csvgetline(FILE *fin) {
    if (fgets(buf, sizeof(buf), fin) == NULL) return -1;

    char *p, *q;
    int nfield = 0;

    for (q = buf; (p = strtok(q, ",\n\r")) != NULL; q = NULL)
        field[nfield++] = unquote(p);

    return nfield;
}


int main(int argc, char *argv[]) {
    int nf = 0;
    while ((nf = csvgetline(stdin)) != -1)
        for (int i = 0; i < nf; i++)
            printf("field[%d] = '%s'\n", i, field[i]);
    return 0;
}
