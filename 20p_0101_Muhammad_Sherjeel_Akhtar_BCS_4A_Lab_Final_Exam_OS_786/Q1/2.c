#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int myGlobal = 0;
pthread_mutex_t myMutex;
int lightI,ThermostatI,SecurityI,AppliancesI,SecurityCI;
void *threadFunction()
{
    int i, j;
        pthread_mutex_lock(&myMutex);
        j = myGlobal;
        j = j+1;
        sleep(1);
        myGlobal = j;
        printf("\n Light Application Started: %d\n", myGlobal);
        lightI=2;
        printf("\n Thermostat Application Started: %d\n", myGlobal);
        ThermostatI=5;
        printf("\n Security Application Started: %d\n", myGlobal);
        SecurityI=10;
        printf("\n Appliances Application Started: %d\n", myGlobal);
        AppliancesI=3;
        printf("\n Security Camera Started: %d\n", myGlobal);
        SecurityCI=4;
        pthread_mutex_unlock(&myMutex);
}
int main(){
    pthread_t myThread;
    int i,k;
    pthread_create(&myThread, NULL,
    threadFunction,NULL);
    pthread_join(myThread, NULL);
        pthread_mutex_lock(&myMutex);
        k = myGlobal;
        k = k+1;
        sleep(1);
        myGlobal = k;
        printf("\n Lights: %d\n", lightI);
        printf("\n Thermostat : %d\n", ThermostatI);
        printf("\n Security System : %d\n", SecurityI);
        printf("\n Appliances : %d\n", AppliancesI);
        printf("\n Security Camera System : %d\n", SecurityCI);
        pthread_mutex_unlock(&myMutex);   
    
        printf("\n Light Application Stopped: %d\n", 0);
        lightI=2;
        printf("\n Thermostat Application Stopped: %d\n", 0);
        ThermostatI=5;
        printf("\n Security Application Stopped: %d\n", 0);
        SecurityI=10;
        printf("\n Appliances Application Stopped: %d\n", 0);
        AppliancesI=3;
        printf("\n Security Camera Stopped: %d\n", 0);

    printf("\nTerminatin My Embedded Operating System: %d\n", myGlobal);
    exit(0);
}