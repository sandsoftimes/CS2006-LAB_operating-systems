#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t water_filter;

int water = 0;
int p1 = 0;
int p2 = 0;
int p3 = 0;
int p4 = 0;
int p5 = 0;

int person = 1;
void* filter(void* arg)
{
    while(person < 6)
    {
        sem_wait(&water_filter);
        water += 10;
        printf("\n10 liters added to water filter. Current water level: %d\n", water);
        sem_post(&mutex);
        sleep(1);
    }
}

void* thread(void* arg)
{
    sem_wait(&mutex);
    if(water >= 5) {
        printf("\nGiving 5 liter water to person %d\n", person);
        p1 += 5;
        water -= 5;
        person +=1;
    }
   else if(water >= 5) {
        printf("\nGiving 5 liter water to person %d\n", person);
        p2 += 5;
        water -= 5;
        person +=1;
    }
    else if(water >= 5) {
        printf("\nGiving 5 liter water to person %d\n", person);
        p3 += 5;
        water -= 5;
        person +=1;
    }
    else if(water >= 5) {
        printf("\nGiving 5 liter water to person %d\n", person);
        p4 += 5;
        water -= 5;
        person +=1;
    }
    else if(water >= 5) {
        printf("\nGiving 5 liter water to person %d\n", person);
        p5 += 5;
        water -= 5;
        person +=1;
    }
    sem_post(&mutex);
    sem_post(&water_filter);

    sleep(1);
}

int main()
{
    sem_init(&mutex, 0, 1);
    sem_init(&water_filter, 0, 1);

    pthread_t t1,t2,t3,t4,t5, f;
    pthread_create(&f, NULL, filter, NULL);
    pthread_create(&t1, NULL, thread, NULL);
    pthread_join(t1, NULL);
    pthread_create(&t2, NULL, thread, NULL);
    pthread_join(t2, NULL);
    pthread_create(&t3, NULL, thread, NULL);
    pthread_join(t3, NULL);
    pthread_create(&t4, NULL, thread, NULL);
    pthread_join(t4, NULL);
    pthread_create(&t5, NULL, thread, NULL);
    pthread_join(t5, NULL);
    
    pthread_join(f, NULL);
    
    
    

    printf("\nTotal water left: %d\n", water);

    sem_destroy(&mutex);
    sem_destroy(&water_filter);

    return 0;
}
