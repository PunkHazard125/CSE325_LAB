#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
sem_t sem;
int counter = 0;

void* mutex_increment(void* arg) {

    for (int i = 0; i < 200000; i++)
    {
        pthread_mutex_lock(&mutex);
        counter++;
        pthread_mutex_unlock(&mutex);
    }

    return NULL;

}

void* sem_increment(void* arg) {

    for (int i = 0; i < 200000; i++)
    {
        sem_wait(&sem);
        counter++;
        sem_post(&sem);
    }

    return NULL;

}

int main() {

    clock_t start, end;
    double cpu_time;

    pthread_t t1, t2;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&sem, 0, 1);

    start = clock();

    pthread_create(&t1, NULL, mutex_increment, NULL);
    pthread_create(&t2, NULL, mutex_increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    end = clock();

    cpu_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.00;

    printf("CPU Time With Mutex: %.2f\n", cpu_time);

    pthread_mutex_destroy(&mutex);

    counter = 0;

    start = clock();

    pthread_create(&t1, NULL, sem_increment, NULL);
    pthread_create(&t2, NULL, sem_increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    end = clock();

    cpu_time = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.00;

    printf("CPU Time With Semaphore: %.2f\n", cpu_time);

    sem_destroy(&sem);

    return 0;

}
