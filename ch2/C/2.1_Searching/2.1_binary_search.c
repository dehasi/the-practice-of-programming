
int binary_search(int arr[], int size, int elem) {

    int l = 0, r = size - 1;

    while (l <= r) {
        int mid = (l + r) / 2; // can be optimized like l + (l-r)/2
        if (arr[mid] == elem) return mid;

        if (arr[mid] < elem) l = mid + 1;
        else r = mid - 1;
    }

    return -1;
}
