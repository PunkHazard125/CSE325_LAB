#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
sem_t wr_sem;
int reader_count = 0;

void* reader(void* arg) {

    int id = (int)(long)arg;
    
    pthread_mutex_lock(&mutex);
    reader_count++;

    if (reader_count == 1)
    {
        sem_wait(&wr_sem);
    }

    pthread_mutex_unlock(&mutex);
    
    printf("Reader %d is reading\n", id);
    sleep(1);

    pthread_mutex_lock(&mutex);
    reader_count--;

    if (reader_count == 0)
    {
        sem_post(&wr_sem);
    }

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* writer(void* arg) {

    int id = (int)(long)arg;
    
    sem_wait(&wr_sem);

    printf("Writer %d is writing\n", id);
    sleep(2);
    
    sem_post(&wr_sem);

    return NULL;
}

int main() {

    pthread_t r1, r2, w1;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wr_sem, 0, 1);

    pthread_create(&r1, NULL, reader, (void*)1);
    pthread_create(&r2, NULL, reader, (void*)2);
    pthread_create(&w1, NULL, writer, (void*)1);

    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    pthread_join(w1, NULL);

    sem_destroy(&wr_sem);
    pthread_mutex_destroy(&mutex);

    return 0;

}
