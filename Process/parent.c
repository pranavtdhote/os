#include <stdio.h>
#include <stdlib.h>

// Binary Search
int binarySearch(int arr[], int n, int key) {
    int low = 0, high = n - 1;

    while(low <= high) {
        int mid = (low + high) / 2;

        if(arr[mid] == key)
            return mid;
        else if(arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main(int argc, char *argv[]) {
    int n = argc - 2;  // last argument is key
    int arr[n];

    // Convert arguments to integers
    for(int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    int key = atoi(argv[argc - 1]);

    printf("\nSorted array received: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nSearching for: %d\n", key);

    int result = binarySearch(arr, n, key);

    if(result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");

    return 0;
}
