/*
    PASSING A RGUMENTS TO THREADS
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *print_message(void* ptr){
    int message;
    message = (int*) ptr;
    printf("\t%d \n", message);
}
void func(void* p){
    void* status=p;
    // printf("Here u go in ld:%ld\n",(long*) status);
    printf("Here u go:%d\n",(int*) status);
}
void func2(void* p){
    void* status2=p;
    printf("Here u go again: %d\n",status2);
}
int main()
{
    pthread_t thread1, thread2,thread3,thread4;
    int x=4;
    int y=5;
    int return_value1, return_value2;
    int return_value3,return_value4;
    return_value1 = pthread_create(&thread1,NULL,print_message, (void*) x);
    return_value2 = pthread_create(&thread2,NULL, print_message, (void*) y);
    return_value3=pthread_create(&thread3,NULL,func,(void*) y);
    return_value4=pthread_create(&thread4,NULL,func2,(void*) x);
    pthread_join(thread1, NULL );
    pthread_join(thread2, NULL );
    pthread_join(thread3,NULL);
    pthread_join(thread4,NULL);
    printf("Display RTValue 4: %d\n",return_value4);
    printf("Display RTValue 3: %d\n",return_value3);
    printf("Ending the main process.\n");
    exit(0);
}