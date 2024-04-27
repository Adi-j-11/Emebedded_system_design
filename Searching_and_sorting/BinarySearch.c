#include <stdio.h>

int binarySearch(int arr[], int size, int key) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {12, 23, 34, 45, 56, 67, 89};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 67;
    int index = binarySearch(arr, size, key);
    if (index != -1) {
        printf("Element %d found at index %d\n", key, index);
    } else {
        printf("Element %d not found in array\n", key);
    }
    return 0;
}
