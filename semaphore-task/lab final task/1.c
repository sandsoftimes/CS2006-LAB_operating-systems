#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_PERSONS 5

sem_t water_filter;
sem_t person_mutex;

void *person(void *arg) {
    int id = *(int*) arg;
    while(1) {
        sem_wait(&person_mutex); // only allow 3 persons to take water at a time
        sem_wait(&water_filter);
        printf("Person %d got 5L of water\n", id);
        sem_post(&water_filter);
        sem_post(&person_mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_PERSONS];
    int ids[NUM_PERSONS];

    // Initialize semaphores
    sem_init(&water_filter, 0, 1); // binary semaphore
    sem_init(&person_mutex, 0, 3); // counting semaphore for 3 persons at a time

    // Create person threads
    for (int i = 0; i < NUM_PERSONS; i++) {
        ids[i] = i+1;
        pthread_create(&threads[i], NULL, person, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_PERSONS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&water_filter);
    sem_destroy(&person_mutex);

    return 0;
}