#include <stdio.h>
#include <cheat.h>

CHEAT_DECLARE(
    int binary_search(int arr[], int size, int elem);

    int nums[] = {1, 2, 3, 6, 7, 9, 12, 16, 25, 35, 42, 51};
)

CHEAT_TEST(name,
    cheat_assert(  5 == binary_search(nums, 12, 9));
    cheat_assert(  5 == binary_search(nums, 12, 9));
    cheat_assert( 11 == binary_search(nums, 12, 51));
    cheat_assert( -1 == binary_search(nums, 12, 4));
    cheat_assert( -1 == binary_search(nums, 12, 52));
    cheat_assert(  0 == binary_search(nums, 12, 1));
    cheat_assert( -1 == binary_search(nums, 12, 0));
)
