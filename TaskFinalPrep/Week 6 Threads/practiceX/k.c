#include <pthread.h>
#include <stdio.h>
struct thread_data
{
    int x, y,z;
};
struct thread2_data{
    int x;
    int y;
    int z;
};
struct thread2_data somedata2;
struct thread_data somedata;
void *print(void *threadArg)
{
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadArg; // type casting from void to thread_data
    printf("X: %d,\nY: %d,\nZ: %d\n",my_data->x, my_data->y, my_data->z);
    // update some va;lue
}
void* func(void* p){
    struct thread2_data *new;
    new=p;
    new->x=100;
    new->y=100;
    new->z=100;
    printf("X: %d and Y: %d and Z: %d\n",new->x,new->y,new->z);
}
int main()
{
    pthread_t tid,tid2;
    somedata.x = 10;
    somedata.y = 20;
    somedata.z = somedata.x + somedata.y;
    somedata2.x=30;
    somedata2.y=40;
    somedata2.z=somedata2.x+somedata2.y;
    pthread_create(&tid, NULL, print, (void *) &somedata);
    pthread_create(&tid2,NULL,func,&somedata2);
    pthread_join(tid, NULL);
    pthread_join(tid2,NULL);
    // print here
    printf("Exiting main.\n");
    return 0;
}