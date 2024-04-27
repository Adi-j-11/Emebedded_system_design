#include <stdio.h>

int main() {
    int arr[] = {12, 34, 45, 67, 89, 23, 56};
    int size = sizeof(arr) / sizeof(arr[0]);
    int key = 67;
    int index = -1; 


    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            index = i; 
            break;
        }
    }

   
    if (index != -1) {
        printf("Element %d found at index %d\n", key, index);
    } else {
        printf("Element not found in array\n")

    return 0;
}
