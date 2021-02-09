#include <stdarg.h>
#include <stdio.h>

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

/* pack: pack binary items into buf, return length */
int pack(uchar *buf, char *fmt, ...) {
    va_list args;
    char *p;
    uchar *bp;
    ushort s;
    ulong l;

    bp = buf;
    va_start(args, fmt);
    for (p = fmt; *p != '\0'; p++) {
        switch (*p) {
            case 'c': /* char */
                *bp++ = va_arg(args, int);
                break;
            case 's': /* short */
                s = va_arg(args, int);
                *bp++ = s >> 8;
                *bp++ = s;
                break;
            case 'l': /* long */
                l = va_arg(args, long);
                *bp++ = l >> 24;
                *bp++ = l >> 16;
                *bp++ = l >> 8;
                *bp++ = l;
                break;
            default: /* illegal type character */
                va_end(args);
                return -1;
        }
    }
    va_end(args);
    return bp - buf;
}


/* unpack: unpack binary items from buf, return length */
int unpack(uchar *buf, char *fmt, ...) {
    va_list args;
    char *p;
    uchar *bp, *pc;
    ushort *ps;
    ulong *pl;

    bp = buf;
    va_start(args, fmt);
    for (p = fmt; *p != '\0'; p++) {
        switch (*p) {
            case 'c': /* char */
                pc = va_arg(args, uchar*);
                *pc = *bp++;
                break;
            case 's': /* short */
                ps = va_arg(args, ushort*);
                *ps = *bp++ << 8;
                *ps |= *bp++;
                break;
            case 'l': /* long */
                pl = va_arg(args, ulong*);
                *pl = *bp++ << 24;
                *pl |= *bp++ << 16;
                *pl |= *bp++ << 8;
                *pl |= *bp++;
                break;
            default: /* illegal type character */
                va_end(args);
                return -1;
        }
    }
    va_end(args);
    return bp - buf;
}

int pack_type1(uchar *buf, ushort count, uchar val, ulong data) {
    return pack(buf, "cscl", 0x01, count, val, data);
}

int unpack_type1(int n, uchar *buf) {
    ushort count;
    uchar val;
    ulong data;
    uchar t;
    if (unpack(buf, "cscl", &t, &count, &val, &data) != n)
        return -1;
    printf("t=%d, count=%d, val=%d, data=%lu\n", t, count, val, data);
    return 0;
}

int (*unpackfn[])(int, uchar*) = {
        unpack_type1,
        unpack_type1
};


int main(int argc, char *argv[]) {
    uchar buf[10];
    int n = pack_type1(buf, 1, 2, 3L);
    unpack_type1(n, buf);
    return 0;
}
