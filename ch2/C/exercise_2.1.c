#include <stdio.h>
#include <stdlib.h>

typedef struct Interval {
    int start, end;
} Interval;

Interval interval(int start, int end) {
    Interval *interval = malloc (sizeof (Interval));
    interval -> start = start;
    interval -> end = end;
    return *interval;
}

void quicksort_iterative(int v[], int n) {
    Interval *intervals = malloc(n * n * sizeof(Interval));
    int cur = 0;
    int last_interval = 0;

    intervals[last_interval++] = interval(0, n);

    while(cur < last_interval) {
        int start = intervals[cur].start, end = intervals[cur].end;

        if ((end - start) <= 1) {
            ++cur;
            continue;
        }

        int pivot = start + ((end - start) / 2);

        int tmp = v[pivot];
        v[pivot] = v[start];
        v[start] = tmp;

        int last = start;
        for (int i = start; i < end; ++i) {
            if (v[i] < v[start]) {
                ++last;
                int tmp = v[last];
                v[last] = v[i];
                v[i] = tmp;
            }
        }

        tmp = v[start];
        v[start] = v[last];
        v[last] = tmp;

        intervals[last_interval++] = interval(start, last);
        intervals[last_interval++] = interval(last + 1, end);

        ++cur;
    }
}

int ints[] = {6,5,4,3,2,1,0};

void print_arr(int v[], int n) {
    for (int i = 0; i < n; i++)
    {
        printf("%i ", v[i]);
    }
    printf("\n");
}
int main2() {
    print_arr(ints, 7);
    quicksort_iterative(ints, 7);
    print_arr(ints, 7);
    return 0;
}
