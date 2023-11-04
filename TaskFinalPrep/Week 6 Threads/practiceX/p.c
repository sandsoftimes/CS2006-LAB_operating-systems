#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int arr1[]={1,2,3};
int arr2[]={1,2,3};
int arr3[]={};
void* func(void* p){
    int status =*((int*)p);
    // while(p!=0){}
    if(status>=0){
        arr3[status]=arr1[status]+arr2[status];
    }
    pthread_exit(NULL);
}
int main(){
    int lenA=sizeof(arr1)/sizeof(arr1[0]);
    int lenB=sizeof(arr2)/sizeof(arr2[0]);
    printf("LengthA:%d:\n",lenA);
    printf("LengthB:%d:\n",lenB);
    if(lenA==lenB){
        pthread_t myThread[lenA];
        int i;
        for(int i=0;i<lenA;i++){
            pthread_create(&myThread[i],NULL,func,&i);
            pthread_join(myThread[i],NULL);// printf("\nHI DUDE");
        }
    }
    else{}
    for(int i=0;i<lenA;i++){
        printf("Value is: %d\n",arr3[i]);
    }
}