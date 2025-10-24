#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>   // for sleep()

#define SIZE 5
int buffer[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&empty);               // Wait for an empty slot
        pthread_mutex_lock(&mutex);     // Enter critical section

        buffer[in] = i;
        printf("Produced: %d\n", i);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&full);                // Signal full slot
        sleep(1);                       // Optional: simulate delay
    }
    return NULL;
}

void* consumer(void* arg) {
    int item;
    for (int i = 1; i <= 5; i++) {
        sem_wait(&full);                // Wait for a full slot
        pthread_mutex_lock(&mutex);     // Enter critical section

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);   // Exit critical section
        sem_post(&empty);               // Signal empty slot
        sleep(1);                       // Optional: simulate delay
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

