#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t empty, full;
pthread_mutex_t mutex;
int item = 0;

void* producer(void* p) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    printf("Produced item %d\n", ++item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}
void* consumer(void* c) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    printf("Consumed item %d\n", item--);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

int main() {
    pthread_t p1, c1;
    sem_init(&empty,0,1);
    sem_init(&full,0,0);
    pthread_mutex_init(&mutex,NULL);

    pthread_create(&p1,NULL,producer,NULL);
    pthread_create(&c1,NULL,consumer,NULL);
    pthread_join(p1,NULL);
    pthread_join(c1,NULL);
    return 0;
}

