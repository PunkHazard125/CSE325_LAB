#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {

    int pid;

    for (int i = 0; i < 3; i++)
    {
        pid = fork();
        
        if (pid == 0)
        {
            printf("Child %d with PID: %d & PPID: %d exiting...\n", i + 1, getpid(), getppid());
            return 0;
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }
    
    printf("Parent with PID: %d exiting after waiting for all 3 child processes\n", getpid());
    
    return 0;

}
