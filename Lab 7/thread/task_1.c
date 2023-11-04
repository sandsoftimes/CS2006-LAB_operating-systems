#include <pthread.h>
#include <stdio.h>
#define ARRAY_SIZE 5 
struct thread_data{
    int *array1;
    int *array2;
    int *result;
    int index;
};
void *add_element(void *threadArg){
    struct thread_data *my_data;
    my_data=(struct thread_data *) threadArg; 
    int index=my_data->index;
    my_data->result[index]=my_data->array1[index]+my_data->array2[index]; 
    pthread_exit(NULL);
}
int main(){
    pthread_t threads[ARRAY_SIZE]; 
    int array1[ARRAY_SIZE]={1,2,3,4,5}; 
    int array2[ARRAY_SIZE]={6,7,8,9,10}; 
    int result[ARRAY_SIZE]; 
    struct thread_data thread_data_array[ARRAY_SIZE]; 
    printf("Array 1: ");
    for (int i=0;i<ARRAY_SIZE;i++){
        printf("%d ",array1[i]);
    }
    printf("\n");
    printf("Array 2: ");
    for (int i=0;i<ARRAY_SIZE;i++){
        printf("%d ",array2[i]);
    }
    printf("\n");
    for (int i=0;i<ARRAY_SIZE;i++){
        thread_data_array[i].array1=array1;
        thread_data_array[i].array2=array2;
        thread_data_array[i].result=result;
        thread_data_array[i].index=i;
        pthread_create(&threads[i],NULL,add_element,(void *) &thread_data_array[i]);
    }
    for (int i=0;i<ARRAY_SIZE;i++){
        pthread_join(threads[i],NULL);
    }
    printf("Result:");
    for (int i=0;i<ARRAY_SIZE;i++){
        printf("%d ",result[i]);
    }
    printf("\n");
    printf("Exiting\n");
    return 0;
}
