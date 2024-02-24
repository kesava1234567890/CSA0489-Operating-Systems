#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int sharedResource = 0;
int readerCount = 0;

sem_t mutex, rw_mutex;

void *reader(void *arg) {
    int readerId = *(int *)arg;

    for (int i = 0; i < 10; ++i) {
        sem_wait(&mutex);
        readerCount++;
        if (readerCount == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Critical section: Reading the shared resource
        printf("Reader %d is reading. Shared Resource: %d\n", readerId, sharedResource);

        sem_wait(&mutex);
        readerCount--;
        if (readerCount == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        // Simulate some delay between reads (moved outside the critical section)
        usleep(500000); // Sleep for 500 milliseconds
    }

    return NULL;
}

void *writer(void *arg) {
    int writerId = *(int *)arg;

    for (int i = 0; i < 10; ++i) {
        sem_wait(&rw_mutex);

        // Critical section: Writing to the shared resource
        sharedResource++;
        printf("Writer %d is writing. Shared Resource: %d\n", writerId, sharedResource);

        sem_post(&rw_mutex);

        // Simulate some delay between writes (moved outside the critical section)
        usleep(1000000); // Sleep for 1 second
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int readerIds[NUM_READERS], writerIds[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        readerIds[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writerIds[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}

