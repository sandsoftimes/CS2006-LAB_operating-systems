#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int kid0(){}
int kid1(){}
int kid2(){}
int kid3(){}
int kid4(){}
int main(){
    void *PrintHello(void *threadid){
        k=a[1]+b[1];
        return k;
    }
    // pthread_t vid0,vid1,vid2,vid3,vid4;
    // pthread_create(&vid0,NULL,kid0,NULL);
    // int *p1;
    // int *p2;
    // p=&arre;
    // p=&arrz;
    // int arre[]={0,1,2,3,4};
    // int arrz[]={0,1,2,3,4};
    // pthread_join(kid0,NULL);
    // pthread_join(kid1,NULL);
    // pthread_join(kid2,NULL);
    // pthread_join(kid3,NULL);
    // printf(arre[4]); 
    // return 0;
    pthread_t thread[5];
    int rc;int t;
    for(t=0;t<5;t++){
        print("Going To Thread: ");
        rc=pthread_create(&thread[t],NULL,PrintHello,void(*)t);
        print(rc);
        exit(-1);
    }
    pthread_join(thread[t],NULL);
}