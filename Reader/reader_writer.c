#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readcount = 0;
int data = 0;

pthread_mutex_t mutex;
sem_t wrt;

// Reader Function
void* reader(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    readcount++;

    if(readcount == 1)
        sem_wait(&wrt); // first reader blocks writer

    pthread_mutex_unlock(&mutex);

    // Critical Section (Reading)
    printf("Reader %d is reading data = %d\n", id, data);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;

    if(readcount == 0)
        sem_post(&wrt); // last reader allows writer

    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Writer Function
void* writer(void* arg) {
    int id = *(int*)arg;

    sem_wait(&wrt); // wait for readers to finish

    // Critical Section (Writing)
    data++;
    printf("Writer %d is writing data = %d\n", id, data);
    sleep(2);

    sem_post(&wrt);

    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int ids[5] = {1,2,3,4,5};
    int wid[2] = {1,2};

    // Create reader threads
    for(int i=0;i<5;i++)
        pthread_create(&r[i], NULL, reader, &ids[i]);

    // Create writer threads
    for(int i=0;i<2;i++)
        pthread_create(&w[i], NULL, writer, &wid[i]);

    // Join threads
    for(int i=0;i<5;i++)
        pthread_join(r[i], NULL);

    for(int i=0;i<2;i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}