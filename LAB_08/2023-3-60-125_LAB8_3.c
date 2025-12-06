#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_THREADS 5

sem_t mutex, barrier;
int counter = 0;

void* thread_job(void* arg) {

    int id = (int)(long)arg;

    printf("Thread %d has reached the barrier\n", id);
    sem_wait(&mutex);

    counter++;
    if (counter == NUM_THREADS)
    {
        sem_post(&barrier);
    }

    sem_post(&mutex);
    
    sem_wait(&barrier);
    sem_post(&barrier);

    printf("Thread %d has passed the barrier\n", id);

    return NULL;

}

int main() {

    pthread_t threads[NUM_THREADS];

    sem_init(&mutex, 0, 1);
    sem_init(&barrier, 0, 0);

    for (long i = 0; i < NUM_THREADS; i++) 
    {
        pthread_create(&threads[i], NULL, thread_job, (void*)i+1);
    }

    for (int i = 0; i < NUM_THREADS; i++) 
    {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&barrier);

    return 0;

}
