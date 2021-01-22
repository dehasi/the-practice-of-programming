#include <stdio.h>
#include <cheat.h>

CHEAT_DECLARE(
    extern void quicksort(int v[], int n);
    extern void quicksort_iterative(int v[], int n);
)

CHEAT_DECLARE(
    int assert_arr_eq(int expected[], int actual[], int size) {
        for (int i = 0; i < size; i++)
            if (expected[i] != actual[i])
                return 1;
        return 0;
    }
)

CHEAT_TEST(sorts,
    int size = 7;
    int array[] = {6,5,4,3,2,1,0};
    int sorted[] = {0,1,2,3,4,5,6};

    quicksort(array, size);

    cheat_assert(assert_arr_eq(array, sorted, size) == 0);
)

CHEAT_TEST(sorts_iterative,
    int size = 7;
    int array[] = {6,5,4,3,2,1,0};
    int sorted[] = {0,1,2,3,4,5,6};

    quicksort_iterative(array, size);

    cheat_assert(assert_arr_eq(array, sorted, size) == 0);
)
