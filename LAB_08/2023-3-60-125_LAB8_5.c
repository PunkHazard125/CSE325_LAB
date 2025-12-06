#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_PRINTERS 3

sem_t sem;

void* printer(void* arg) {

    int id = (int)(long)arg;

    printf("Thread %d is waiting for a printer...\n", id);
    sem_wait(&sem);

    printf("Thread %d is using a printer.\n", id);
    sleep(2);

    printf("Thread %d has finished using the printer.\n", id);
    sem_post(&sem);

    return NULL;

}

int main() {

    pthread_t threads[NUM_THREADS];

    sem_init(&sem, 0, NUM_PRINTERS);

    for (long i = 0; i < NUM_THREADS; i++) 
    {
        pthread_create(&threads[i], NULL, printer, (void*)i+1);
    }

    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&sem);

    return 0;

}
