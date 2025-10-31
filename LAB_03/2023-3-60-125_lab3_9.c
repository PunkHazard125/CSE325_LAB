#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {

    int pid = fork();

    if (pid == 0)
    {
        printf("First Child Process (PID: %d) exiting...", getpid());
        _exit(0);
    }
    else
    {
        pid = fork();

        if (pid == 0)
        {
            sleep(2);
            printf("Second Child Process (PID: %d) exiting...", getpid());
            exit(0);
        }

        sleep(4);
        printf("\nParent Process (PID: %d) exiting...\n", getpid());
    }
    
    return 0;

}
