#include <stdio.h>
#include <pthread.h>
#include <time.h>

int counter = 0;
pthread_mutex_t lock;

void* unsafe_increment(void* arg) {

    for (int i = 0; i < 200000; i++)
    {
        counter++;
    }

    return NULL;

}

void* safe_increment(void* arg) {

    for (int i = 0; i < 200000; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;

}

int main(void) {

    clock_t start, end;
    double cpu_time;
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    start = clock();
    pthread_create(&t1, NULL, unsafe_increment, NULL);
    pthread_join(t1, NULL);
    end = clock();

    cpu_time = (((double)(end - start)) / CLOCKS_PER_SEC ) * 1000.0;
    printf("CPU Time Without Mutex: %.2fms\n", cpu_time);

    counter = 0;
    start = clock();
    pthread_create(&t2, NULL, safe_increment, NULL);
    pthread_join(t2, NULL);
    end = clock();

    cpu_time = (((double)(end - start)) / CLOCKS_PER_SEC ) * 1000.0;
    printf("CPU Time With Mutex:    %.2fms\n", cpu_time);

    pthread_mutex_destroy(&lock);

    return 0;

}
