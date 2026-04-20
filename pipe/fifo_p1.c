#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define SIZE 1024

int main()
{
    int fd1, fd2;
    char input[SIZE], output[SIZE];

    // Create FIFO (ignore error if already exists)
    mkfifo("fifo1", 0666);
    mkfifo("fifo2", 0666);

    // Open FIFOs
    fd1 = open("fifo1", O_WRONLY);
    fd2 = open("fifo2", O_RDONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        perror("Error opening FIFO");
        exit(1);
    }

    printf("Enter a sentence: ");
    fgets(input, SIZE, stdin);

    // Send input to Process 2
    write(fd1, input, strlen(input) + 1);

    // Read result from Process 2
    read(fd2, output, SIZE);
    printf("\nResult from Process 2:\n%s\n", output);

    close(fd1);
    close(fd2);

    return 0;
}

//mkfifo fifo1
//mkfifo fifo2
