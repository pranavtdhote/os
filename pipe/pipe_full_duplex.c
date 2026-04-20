#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int fd1[2], fd2[2];
    pid_t pid;

    char filename[100], buffer[1000];

    pipe(fd1);
    pipe(fd2);

    pid = fork();

    if(pid > 0) {
        // PARENT
        close(fd1[0]); // close read
        close(fd2[1]); // close write

        printf("Enter filename: ");
        scanf("%s", filename);

        write(fd1[1], filename, strlen(filename)+1);

        read(fd2[0], buffer, sizeof(buffer));
        printf("\nFile contents:\n%s\n", buffer);
    }
    else {
        // CHILD
        close(fd1[1]);
        close(fd2[0]);

        read(fd1[0], filename, sizeof(filename));

        FILE *fp = fopen(filename, "r");

        if(fp == NULL) {
            strcpy(buffer, "File not found");
        } else {
            fread(buffer, sizeof(char), sizeof(buffer), fp);
            fclose(fp);
        }

        write(fd2[1], buffer, strlen(buffer)+1);
    }

    return 0;
}