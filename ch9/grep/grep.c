#include "eprintf.h"
#include <stdio.h>
#include <string.h>

int matchhere(char *regexp, char *text);
int matchstar(int c, char *regexp, char *text);

/* match: search for regexp anywhere in text */
int match(char *regexp, char *text) {
    if (regexp[0] == '^')
        return matchhere(regexp + 1, text);
    do {
        if (matchhere(regexp, text))
            return 1;
    } while (*text++ != '\0');
    return 0;
}

/* matchhere: search for regexp at beginning of text */
int matchhere(char *regexp, char *text) {
    if (regexp[0] == '\0')
        return 1;
    if (regexp[1] == '*')
        return matchstar(regexp[0], regexp + 2, text);
    if (regexp[0] == '$' && regexp[1] == '\0')
        return *text == '\0';
    if (*text != '\0' && (regexp[0] == '.' || regexp[0] == *text))
        return matchhere(regexp + 1, text + 1);
    return 0;
}

/* matchstar: search for c*regexp at beginning of text */
int matchstar0(int c, char *regexp, char *text) {
    do { /* a * matches zero or more instances */
        if (matchhere(regexp, text))
            return 1;
    } while (*text != '\0' && (*text++ == c || c == '.'));
    return 0;
}

/* matchstar: leftmost longest search for c*regexp */
int matchstar(int c, char *regexp, char *text) {
    char *t;
    for (t = text; *t != '\0' && (*t == c || c == '.'); t++);

    do { /* * matches zero or more */
        if (matchhere(regexp, t))
            return 1;
    } while (t-- > text);
    return 0;
}

/* grep: seatch for regexp in file */
int grep(char *regexp, FILE *f, char *name) {
    char buf[BUFSIZ];
    int nmatch = 0;
    while (fgets(buf, sizeof buf, f) != NULL) {
        int n = strlen(buf);
        if (n > 0 && buf[n - 1] == '\n')
            buf[n - 1] = '\0';
        if (match(regexp, buf)) {
            ++nmatch;
            if (name != NULL) printf("%s:", name);
            printf("%s\n", buf);
        }
    }
    return nmatch;
}

int main(int argc, char *argv[]) {
    setprogname("grep");
    if (argc < 2)
        eprintf("usage: grep regexp [file ...]");
    int nmatch = 0;
    if (argc == 2) {
        if (grep(argv[1], stdin, NULL))
            ++nmatch;
    } else {
        for (int i = 2; i < argc; ++i) {
            FILE *f = fopen(argv[i], "r");
            if (f == NULL) {
                weprintf("can't open %s:", argv[i]);
                continue;
            }
            if (grep(argv[1], f, argc > 3 ? argv[i] : NULL) > 0)
                ++nmatch;
            fclose(f);
        }
    }
    return nmatch == 0;
}
