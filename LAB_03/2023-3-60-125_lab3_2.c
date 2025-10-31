#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {

    int pid[4];

    pid[0] = fork();

    if (pid[0] == 0)
    {
        printf("Child %d, PID: %d exiting...\n", 1, getpid());
        return 0;
    }
    
    wait(NULL);
    printf("\nParent: Waited for Child 1 with PID: %d using wait()\n\n", pid[0]);

    for (int i = 1; i < 4; i++)
    {
        pid[i] = fork();
        
        if (pid[i] == 0)
        {
            printf("Child %d, PID: %d exiting...\n", i + 1, getpid());
            sleep(2 + i);
            return 0;
        }
    }

    printf("\n");

    for (int i = 3; i >= 1; i--)
    {
        waitpid(pid[i], NULL, 0);
        printf("Parent: Waited for Child %d with PID: %d using waitpid()\n", i + 1, pid[i]);
    }
    
    return 0;

}
