#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void handler(int signum) {

    printf("Signal %d received. Process terminated safely.\n", signum);
    _exit(0);

}

int main(void) {

    signal(SIGINT, handler);
    signal(SIGTERM, handler);

    printf("PID: %d\n", getpid());

    while (1)
    {
        printf("Process is running...\n");
        sleep(2);
    }
    
    return 0;

}
