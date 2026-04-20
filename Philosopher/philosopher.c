#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];
sem_t room;

void* philosopher(void* num) {
    int id = *(int*)num;

    while(1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        sem_wait(&room); // limit to 4 philosophers

        sem_wait(&chopstick[id]); // left
        sem_wait(&chopstick[(id+1)%N]); // right

        printf("Philosopher %d is eating\n", id);
        sleep(2);

        sem_post(&chopstick[id]);
        sem_post(&chopstick[(id+1)%N]);

        sem_post(&room); // leave room
    }
}

int main() {
    pthread_t phil[N];
    int ids[N];

    sem_init(&room, 0, 4);

    for(int i=0;i<N;i++)
        sem_init(&chopstick[i], 0, 1);

    for(int i=0;i<N;i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }

    for(int i=0;i<N;i++)
        pthread_join(phil[i], NULL);

    return 0;
}