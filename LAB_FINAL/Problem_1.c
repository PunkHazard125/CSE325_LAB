#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 5
#define MAX_THREADS 8

int stack[MAX_SIZE];
int top = -1;

pthread_mutex_t mutex;

void* push(void* arg) {

    int id = (int)(long)arg;
    int act_count = 0;
    int act_limit = rand() % 2 + 3;

    while (1)
    {
        if (act_count == act_limit)
        {
            printf("Thread %d terminated\n", id);
            break;
        }
        
        pthread_mutex_lock(&mutex);

        if (top + 1 == MAX_SIZE)
        {
            printf("Thread %d failed to push into stack because of overflow\n", id);
            pthread_mutex_unlock(&mutex);

            act_count++;
            usleep((rand() % 500 + 500) * 1000);
            continue;
        }
        
        int number = rand() % 10 + 1;
        stack[++top] = number;
        act_count++;

        printf("Thread %d pushed %d into stack | Current Size: %d\n", id, number, top + 1);

        pthread_mutex_unlock(&mutex);
        usleep((rand() % 500 + 500) * 1000);
    }

    return NULL;

}

void* pop(void* arg) {

    int id = (int)(long)arg;
    int act_count = 0;
    int act_limit = rand() % 2 + 3;

    while (1)
    {
        if (act_count == act_limit)
        {
            printf("Thread %d terminated\n", id);
            break;
        }

        pthread_mutex_lock(&mutex);

        if (top == -1)
        {
            printf("Thread %d failed to pop from stack because of underflow\n", id);
            pthread_mutex_unlock(&mutex);

            act_count++;
            usleep((rand() % 500 + 500) * 1000);
            continue;
        }

        int val = stack[top--];
        act_count++;

        printf("Thread %d popped %d from stack | Current Size: %d\n", id, val, top + 1);

        pthread_mutex_unlock(&mutex);
        usleep((rand() % 500 + 500) * 1000);
    }

    return NULL;

}

int main(void) {

    pthread_t thread[MAX_THREADS];
    pthread_mutex_init(&mutex, NULL);
    srand(time(NULL));

    for (int i = 0; i < MAX_THREADS; i++)
    {
        int action = rand() % 2;

        if (action == 0)
        {
            pthread_create(&thread[i], NULL, push, (void*)(long)(i+1));
        }
        else
        {
            pthread_create(&thread[i], NULL, pop, (void*)(long)(i+1));
        }
    }
    
    for (int i = 0; i < MAX_THREADS; i++)
    {
        pthread_join(thread[i], NULL); 
    }

    pthread_mutex_destroy(&mutex);

    return 0;

}
