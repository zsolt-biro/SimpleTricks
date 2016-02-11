#include <stdio.h>
#include <unistd.h>
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main(void)
{
    char str[100];
    int saved_out=dup(fileno(stdout));
    int saved_in=dup(fileno(stdin));
    int my_pipe[2];
    //create pipe
    if(pipe(my_pipe) == -1)
    {
        fprintf(stderr, "Error creating pipe\n");
    }

    
    if (dup2(my_pipe[1], fileno(stdout))==-1)
        printf("can't redirect stdout \n");
    if (dup2(my_pipe[0], fileno(stdin))==-1)
        printf("can't redirect stdin\n");
    printf("ThisStringWillBeRedirectedToStdin\n");
    fflush(stdout);
    scanf("%s", str);
    if (dup2(saved_out, fileno(stdout))==-1)
        printf("can't restore stdout\n");
    if (dup2(saved_in, fileno(stdin))==-1)
        printf("can't restore stdout\n");
    close(my_pipe[0]);
    close(my_pipe[1]);
    close(saved_out);
    close(saved_in);

    printf("We've got: %s\n", str);


}