
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define BUFFER_SIZE 5
#define ITEMS 20

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int count;
    int producer_done;

    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} SharedData;

SharedData shared = {
    .mutex = PTHREAD_MUTEX_INITIALIZER,
    .not_empty = PTHREAD_COND_INITIALIZER,
    .not_full = PTHREAD_COND_INITIALIZER
};

/* Producer thread */
void* producer(void* arg) {
    (void)arg;

    for (int i = 1; i <= ITEMS; i++) {
        pthread_mutex_lock(&shared.mutex);

        while (shared.count == BUFFER_SIZE &&
               !shared.producer_done) {
            pthread_cond_wait(&shared.not_full, &shared.mutex);
        }

        if (shared.producer_done) {
            pthread_mutex_unlock(&shared.mutex);
            return NULL;
        }

        shared.buffer[shared.in] = i;
        shared.in = (shared.in + 1) % BUFFER_SIZE;
        shared.count++;

        printf("Produced: %d | Buffer items: %d\n",
               i, shared.count);

        pthread_cond_signal(&shared.not_empty);
        pthread_mutex_unlock(&shared.mutex);
    }

    pthread_mutex_lock(&shared.mutex);
    shared.producer_done = 1;

    pthread_cond_signal(&shared.not_empty);
    pthread_mutex_unlock(&shared.mutex);

    return NULL;
}

/* Consumer thread */
void *consumer(void *arg) {
    (void)arg;

    for (;;) {
        pthread_mutex_lock(&shared.mutex);

        while (shared.count == 0 && !shared.producer_done) {
            pthread_cond_wait(&shared.not_empty, &shared.mutex);
        }

        if (shared.count == 0 && shared.producer_done) {
            pthread_mutex_unlock(&shared.mutex);
            break;
        }

        int value = shared.buffer[shared.out];
        shared.out = (shared.out + 1) % BUFFER_SIZE;
        shared.count--;

        printf("Consumed: %d | Buffer items: %d\n",
               value, shared.count);

        pthread_cond_signal(&shared.not_full);
        pthread_mutex_unlock(&shared.mutex);
    }

    return NULL;
}

int main(void) {
    pthread_t producer_thread;
    pthread_t consumer_thread;

    int result = pthread_create(
        &producer_thread, NULL, producer, NULL
    );

    if (result != 0) {
        printf("Could not create producer thread: %s\n",
               strerror(result));
        return 1;
    }

    result = pthread_create(
        &consumer_thread, NULL, consumer, NULL
    );

    if (result != 0) {
        printf("Could not create consumer thread: %s\n",
               strerror(result));

        pthread_mutex_lock(&shared.mutex);
        shared.producer_done = 1;
        pthread_cond_broadcast(&shared.not_full);
        pthread_mutex_unlock(&shared.mutex);

        pthread_join(producer_thread, NULL);
        return 1;
    }

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&shared.mutex);
    pthread_cond_destroy(&shared.not_empty);
    pthread_cond_destroy(&shared.not_full);

    printf("\nAll items produced and consumed.\n");

    return 0;
}
