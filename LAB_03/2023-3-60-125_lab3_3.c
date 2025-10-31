#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {

    printf("Root Parent with PID: %d creating a child...\n", getpid());

    int pid1 = fork();

    if (pid1 == 0)
    {
        printf("Child PID: %d with Parent PID: %d creating another child...\n", getpid(), getppid());

        int pid2 = fork();

        if (pid2 == 0)
        {
            printf("Child PID: %d with Parent PID: %d exiting...\n", getpid(), getppid());
            return 0;
        }

        wait(NULL);
    }
    else
    {
        wait(NULL);
    }
    
    return 0;

}
