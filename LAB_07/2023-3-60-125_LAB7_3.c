#include <stdio.h>
#include <pthread.h>

int arr[5] = {2, 4, 6, 8, 10};
pthread_mutex_t lock;

void* update_arr(void* arg) {

    pthread_mutex_lock(&lock);

    for (int i = 0; i < 5; i++)
    {
        arr[i] *= 2;
    }

    pthread_mutex_unlock(&lock);

    return NULL;

}

int main(void) {

    printf("Array Before Updates: ");

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, update_arr, NULL);
    pthread_create(&t2, NULL, update_arr, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("\nArray After Updates: ");

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    
    printf("\n");

    return 0;

}
