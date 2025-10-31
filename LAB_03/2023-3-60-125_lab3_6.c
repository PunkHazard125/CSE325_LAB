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
            sleep(3);
            printf("Child process (PID: %d) is now orphaned, adopted by init (PID: %d)\n", getpid(), getppid());
            return 0;
        }
    }
    
    printf("Parent process (PID: %d) exiting...\n\n", getpid());
    sleep(1);
    
    return 0;

}
