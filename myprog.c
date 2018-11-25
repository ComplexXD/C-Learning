#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(void)
{

    char* buff = malloc(100);
    
    int file = open("readme.txt", O_RDONLY);
    
    int n = read(file, buff, 100);

    close(file);

    int file2 = open("readme2.txt", O_RDWR | O_CREAT, 0666);

    write(file2, buff, n);

    close(file2);

    free(buff);

    return 0;
}