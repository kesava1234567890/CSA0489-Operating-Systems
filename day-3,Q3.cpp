#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Shared data
int sharedVariable = 0;

// Mutex for synchronization
pthread_mutex_t mutex;

// Function to be executed by each thread
void *threadFunction(void *arg) {
    int threadId = *(int *)arg;

    for (int i = 0; i < 5; ++i) {
        // Lock the mutex before accessing the shared variable
        pthread_mutex_lock(&mutex);

        // Critical section: Access and modify the shared variable
        printf("Thread %d: Shared variable before increment: %d\n", threadId, sharedVariable);
        sharedVariable++;
        printf("Thread %d: Shared variable after increment: %d\n", threadId, sharedVariable);

        // Unlock the mutex after finishing the critical section
        pthread_mutex_unlock(&mutex);

        // Simulate some work being done by the thread
        usleep(100000); // Sleep for 100 milliseconds
    }

    return NULL;
}

int main() {
    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        fprintf(stderr, "Mutex initialization failed\n");
        return 1;
    }

    // Create two threads
    pthread_t thread1, thread2;
    int threadId1 = 1, threadId2 = 2;

    if (pthread_create(&thread1, NULL, threadFunction, &threadId1) != 0) {
        fprintf(stderr, "Thread creation failed\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, threadFunction, &threadId2) != 0) {
        fprintf(stderr, "Thread creation failed\n");
        return 1;
    }

    // Wait for both threads to finish
    if (pthread_join(thread1, NULL) != 0) {
        fprintf(stderr, "Thread join failed\n");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        fprintf(stderr, "Thread join failed\n");
        return 1;
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}

