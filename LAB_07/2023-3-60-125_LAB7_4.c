#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int supply = 0, is_full = 0, item = 0;
pthread_mutex_t lock;

void* producer(void* arg) {

    while (1)
    {
        while (is_full == 1) { }
        
        pthread_mutex_lock(&lock);

        if (is_full == 0)
        {
            supply++;
            item++;
            is_full = 1;

            printf("Producer produced item #%d\n", item);
            sleep(1);
        }

        pthread_mutex_unlock(&lock);

        if (item == 5)
        {
            break;
        }
    }

    return NULL;

}

void* consumer(void* arg) {

    while (1)
    {
        while (is_full == 0) { }
        
        pthread_mutex_lock(&lock);

        if (is_full == 1)
        {
            supply--;
            is_full = 0;
            printf("Consumer consumed item #%d\n", item);
            sleep(1);
        }

        pthread_mutex_unlock(&lock);

        if (item == 5)
        {
            break;
        }
    }

    return NULL;

}

int main(void) {

    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    return 0;

}
