#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_CMD 10

int main() {
    
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    char *history[MAX_INPUT];

    pid_t pid;
    int status;
    int cmd_count = 0;

    while (1)
    {

        printf("mysh>> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break;
        }

        if (strlen(input) == 0)
        {
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (cmd_count == MAX_CMD)
        {
            free(history[0]);

            for (int i = 1; i < cmd_count; i++)
            {
                history[i - 1] = history[i];
            }

            cmd_count--;
        }
        
        history[cmd_count] = malloc(MAX_INPUT);
        strncpy(history[cmd_count], input, sizeof(input));
        cmd_count++;

        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        if (strcmp(input, "history") == 0)
        {
            for (int i = 0; i < cmd_count; i++)
            {
                printf("%d. %s\n", i + 1, history[i]);
            }
            
            continue;
        }
        
        char *token = strtok(input, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        
        args[i] = NULL;

        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                fprintf(stderr, "mysh: missing argument to \"cd\"\n");
                continue;
            }
            else
            {
                if (chdir(args[1]) != 0)
                {
                    perror("mysh");
                }
            }

            continue;
        }

        pid = fork();

        if (pid == 0)
        {
            if (execvp(args[0], args) == -1)
            {
                perror("mysh");
            }
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);
        }
        else
        {
            perror("fork failed");
        }
        
    }

    for (int i = 0; i < cmd_count; i++)
    {
        free(history[i]);
    }

    return 0;

}
