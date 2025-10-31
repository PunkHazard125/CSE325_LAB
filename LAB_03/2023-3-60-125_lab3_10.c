#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {

    int pid = fork();

    if (pid == 0)
    {
        printf("Normal Child Process (PID: %d) with Parent (PID: %d) exiting\n", getpid(), getppid());
        return 0;
    }
    else
    {
        wait(NULL);
        printf("Parent (PID: %d) waited for the normal child to finish\n", getpid());

        pid = fork();

        if (pid == 0)
        {
            sleep(1);
            printf("Zombie Child Process (PID: %d) exiting before Parent (PID: %d)\n", getpid(), getppid());
            return 0;
        }

        sleep(3);
        printf("Parent (PID: %d) did not use wait() for the second child\n", getpid());

        pid = fork();

        if (pid == 0)
        {
            sleep(5);
            printf("Orphan Child Process (PID: %d) adopted by init (PID: %d)\n", getpid(), getppid());
            return 0;
        }
        
        sleep(2);
        printf("Parent (PID: %d) is exiting before the last child could finish\n", getpid());
    }
    
    return 0;

}
