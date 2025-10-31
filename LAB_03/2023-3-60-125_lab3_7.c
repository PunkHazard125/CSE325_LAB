#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {

    int pid = fork();

    if (pid == 0)
    {
        printf("Child process (PID: %d) exiting...\n", getpid());
    }
    else
    {
        pid = fork();

        if (pid == 0)
        {
            printf("Child process (PID: %d) exiting...\n", getpid());
            return 0;
        }

        sleep(2);
        printf("Parent process (PID: %d) sleeping, not collecting any child's exit status...\n", getpid());
        sleep(3);
    }
    
    return 0;

}
