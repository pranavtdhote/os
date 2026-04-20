#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0, out = 0;

pthread_mutex_t mutex;
sem_t empty, full;

// Producer Function
void* producer(void* arg) {
    int item;

    for(int i = 0; i < 10; i++) {
        item = rand() % 100;

        sem_wait(&empty); // wait for empty slot
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full); // increase full count

        sleep(1);
    }
}

// Consumer Function
void* consumer(void* arg) {
    int item;

    for(int i = 0; i < 10; i++) {

        sem_wait(&full); // wait for item
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); // increase empty count

        sleep(2);
    }
}

int main() {
    pthread_t p, c;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}