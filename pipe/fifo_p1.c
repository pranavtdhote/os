#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1, fd2;
    char input[200], output[200];

    fd1 = open("fifo1", O_WRONLY);
    fd2 = open("fifo2", O_RDONLY);

    printf("Enter sentence: ");
    fgets(input, sizeof(input), stdin);

    write(fd1, input, strlen(input)+1);

    read(fd2, output, sizeof(output));

    printf("\nResult from Process 2:\n%s\n", output);

    return 0;
}