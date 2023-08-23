#include "utils/68k.h"

/* Function to swap two elements */
void c_swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Partition function */
int c_partition(int arr[], int low, int high) {
    int pivot = arr[high]; /* Choosing the last element as the pivot */
    int i = (low - 1);     /* Index of smaller element */
    int j;

    for (j = low; j < high; j++) {
        /* If current element is smaller than or equal to the pivot */
        if (arr[j] <= pivot) {
            i++; /* Increment index of smaller element */
            c_swap(&arr[i], &arr[j]);
        }
    }
    c_swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* Quicksort function */
void c_quicksort(int arr[], int low, int high) {
    int pivotIndex;
    if (low < high) {
        /* Partition the array into two sub-arrays and get the pivot index */
        pivotIndex = c_partition(arr, low, high);

        /* Recursive call on the left and right sub-arrays */
        c_quicksort(arr, low, pivotIndex - 1);
        c_quicksort(arr, pivotIndex + 1, high);
    }
}

/* Utility function to print an array */
void c_printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\r\n");
}

int c_main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \r\n");
    c_printArray(arr, n);

    c_quicksort(arr, 0, n - 1);

    printf("Sorted array: \r\n");
    c_printArray(arr, n);

    return 0;
}
