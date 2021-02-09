#ifndef UNTITLED_EPRINTF_H
#define UNTITLED_EPRINTF_H

#include <stdlib.h>

extern void weprintf(const char *fmt, ...);

extern void eprintf(const char *fmt, ...);

extern char *estrdup(const char *s);

extern void *emalloc(void *ptr, size_t n);

extern void *erealloc(void *ptr, size_t n);

extern char *progname();

extern void setprogname(const char *str);

#endif //UNTITLED_EPRINTF_H
