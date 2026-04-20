#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd1, fd2;
    char input[200];
    int chars = 0, words = 0, lines = 0;

    fd1 = open("fifo1", O_RDONLY);
    fd2 = open("fifo2", O_WRONLY);

    read(fd1, input, sizeof(input));

    for(int i=0; input[i] != '\0'; i++) {
        chars++;
        if(input[i] == ' ')
            words++;
        if(input[i] == '\n')
            lines++;
    }

    words++; // last word

    char result[200];
    sprintf(result, "Chars: %d Words: %d Lines: %d", chars, words, lines);

    FILE *fp = fopen("output.txt", "w");
    fprintf(fp, "%s", result);
    fclose(fp);

    write(fd2, result, strlen(result)+1);

    return 0;
}