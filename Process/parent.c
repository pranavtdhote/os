#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// Bubble sort
void sort(int arr[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter size: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort array
    sort(arr, n);

    int key;
    printf("Enter element to search: ");
    scanf("%d", &key);

    // Prepare arguments for execve
    char *args[n + 3];
    args[0] = "./child";

    // Convert array elements to string
    for(int i = 0; i < n; i++) {
        args[i + 1] = (char*)malloc(10);
        sprintf(args[i + 1], "%d", arr[i]);
    }

    // Convert key to string (FIXED)
    args[n + 1] = (char*)malloc(10);
    sprintf(args[n + 1], "%d", key);

    args[n + 2] = NULL;

    int pid = fork();

    if(pid == 0) {
        // CHILD PROCESS
        execve("./child", args, NULL);
        perror("execve failed");
        exit(1);
    } 
    else if(pid > 0) {
        // PARENT PROCESS
        wait(NULL);
        printf("Parent process finished\n");
    } 
    else {
        printf("Fork failed\n");
    }

    return 0;
}
