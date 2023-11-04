#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
int glob_data = 5;
void *kidfunc(void *p)
{
    printf ("Kid here:- Global data was %d.\n", glob_data);
    glob_data = 15;
    printf ("Kid Again:- Global data was now %d.\n", glob_data);
}
void *func(void* p){
    printf("Kid func2 here:- Global data was %d\n",glob_data);
    glob_data=50;
    printf("Globa Data Now %d\n",glob_data);
}
int main()
{
    pthread_t kid;
    pthread_t kid2;
    pthread_create (&kid, NULL, kidfunc, NULL);
    printf ("Parent at Start:- Global data = %d\n", glob_data);
    pthread_create(&kid2,NULL,func,NULL);
    pthread_join(kid,NULL);
    glob_data = 10;
    pthread_join(kid2,NULL);
    printf ("End of program.\nGlobal data = %d\n", glob_data);
    return 0;
}


