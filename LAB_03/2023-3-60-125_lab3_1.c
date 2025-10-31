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
            printf("Child %d, PID: %d, PPID: %d\n", i + 1, getpid(), getppid());
            return 0;
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        wait(NULL);
    }
    
    return 0;

}
