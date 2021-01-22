#ifndef MY_ASSERT_H
#define MY_ASSERT_H
#include <stdio.h>

int assert_eq(int expected, int actual) {
    if (expected != actual) {
        printf("NOK: %i != %i\n", expected, actual);
        return 1;
    } 
    printf("OK: %i == %i\n", expected, actual);
    return 0;
}

void report_errors(int errors) {
    if (errors) printf("FAIL: %i errors\n", errors);
    else printf("OK\n");
}
#endif