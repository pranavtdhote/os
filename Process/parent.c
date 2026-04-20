#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
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
    for(int i=0;i<n;i++)
        scanf("%d", &arr[i]);

    sort(arr, n);

    int pid = fork();

    if(pid == 0) {
        char *args[n+2];

        args[0] = "./child";

        for(int i=0;i<n;i++) {
            args[i+1] = (char*)malloc(10);
            sprintf(args[i+1], "%d", arr[i]);
        }

        args[n+1] = NULL;

        execve("./child", args, NULL);
    }

    return 0;
}