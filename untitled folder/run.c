# include "minishell.h"

void    lk(void) {system("leaks run");}
int main  (void )
{
    char    *run;

    atexit (lk);
    run = readline("HELLO: ");
    int pid = fork();
    if (pid == 0)
    {
        printf("%s\n", run);
        free(run);
        // exit(0);
    }
    waitpid(pid, NULL ,0);
    sleep(4);
    // ft_allocate(36,0);
    // sleep (100);
}
