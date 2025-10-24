#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int read_count = 0, data = 1;
sem_t wrt;
pthread_mutex_t mutex;

void* reader(void* arg) {
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt);
    pthread_mutex_unlock(&mutex);

    printf("Reader read: %d\n", data);

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* writer(void* arg) {
    sem_wait(&wrt);
    data *= 2;
    printf("Writer wrote: %d\n", data);
    sem_post(&wrt);
    return NULL;
}

int main() {
    pthread_t r1, r2, w1;

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&r2, NULL, reader, NULL);

    pthread_join(r1, NULL);
    pthread_join(w1, NULL);
    pthread_join(r2, NULL);

    return 0;
}
