#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024

int main()
{
    int fd1, fd2;
    char input[SIZE], result[SIZE];
    int chars = 0, words = 0, lines = 0;

    // Open FIFOs
    fd1 = open("fifo1", O_RDONLY);
    fd2 = open("fifo2", O_WRONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        perror("Error opening FIFO");
        exit(1);
    }

    // Read input
    read(fd1, input, SIZE);

    // Count logic
    for (int i = 0; input[i] != '\0'; i++)
    {
        chars++;

        if (input[i] == ' ')
            words++;

        if (input[i] == '\n')
            lines++;
    }

    if (chars > 0)
        words++; // last word

    // Prepare result string (NO FILE NEEDED ❌)
    sprintf(result,
            "Characters: %d\nWords: %d\nLines: %d\n",
            chars, words, lines);

    // Send result back
    write(fd2, result, strlen(result) + 1);

    close(fd1);
    close(fd2);

    return 0;
}
