#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define COUNT_LIMIT 100000

long long counter = 0;             // Shared resource
pthread_mutex_t lock;              // Mutex declaration

void* increment_counter(void* arg) {
    for (int i = 0; i < COUNT_LIMIT; i++) {
        // Lock before entering critical section
        pthread_mutex_lock(&lock);
        counter++;  // Critical section
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    // Create threads
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    // Display result
    printf("Expected Counter Value: %lld\n", (long long)NUM_THREADS * COUNT_LIMIT);
    printf("Final Counter Value   : %lld\n", counter);

    return 0;
}

