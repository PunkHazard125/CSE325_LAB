#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0, next_item = 1;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {

    int id = (int)(long)arg;
    
    for (int i = 1; i <= 5; i++) 
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        int curr_item = next_item++;
        buffer[count++] = curr_item;
        printf("Producer %d -> Produced: %d | Buffer count: %d\n", id, curr_item, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }

    return NULL;
}

void* consumer(void* arg) {

    int id = (int)(long)arg;
    
    for (int i = 1; i <= 5; i++) 
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[--count];
        printf("Consumer %d -> Consumed: %d | Buffer count: %d\n", id, item, count);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    
    return NULL;
}

int main() {

    pthread_t prod1, prod2, cons1, cons2;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod1, NULL, producer, (void*)1);
    pthread_create(&cons1, NULL, consumer, (void*)1);
    pthread_create(&prod2, NULL, producer, (void*)2);
    pthread_create(&cons2, NULL, consumer, (void*)2);

    pthread_join(prod1, NULL);
    pthread_join(cons1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(cons2, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;

}
