#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    int saved_out=dup(fileno(stdout));
    int f = open("test.txt", O_WRONLY | O_CREAT);
    if (f == -1)
        printf("Can't open file\n");
    
    if (dup2(f, fileno(stdout))==-1)
        printf("can't redirect stdout \n");

    printf("ThisStringWillBeRedirectedToFile\n");
    fflush(stdout);
    
    if (dup2(saved_out, fileno(stdout))==-1)
        printf("can't restore stdout\n");

    close(saved_out);

    printf("This should appear on stdout\n");


}