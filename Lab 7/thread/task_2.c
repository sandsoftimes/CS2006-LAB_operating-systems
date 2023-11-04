#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
struct thread_data {
    int width;
    int height;
    int area;
    int perimeter;
};
void *compute_area(void *arg) {
    struct thread_data *data=(struct thread_data*) arg;
    data->area=data->width*data->height;
    printf("Thread %ld computed the area:%d\n",pthread_self(),data->area);
    pthread_exit(NULL);
}
void *compute_perimeter(void *arg) {
    struct thread_data *data=(struct thread_data*) arg;
    data->perimeter=2*(data->width+data->height);
    printf("Thread %ld computed the perimeter:%d\n",pthread_self(),data->perimeter);
    pthread_exit(NULL);
}
int main() {
    pthread_t threads[2];
    struct thread_data data={0,0,0,0};
    printf("Enter the width and height of the rectangle:");
    scanf("%d %d",&data.width,&data.height);
    pthread_create(&threads[0],NULL,compute_area,(void*)&data);
    pthread_create(&threads[1],NULL,compute_perimeter,(void*)&data);
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
    printf("The area of the rectangle is:%d\n",data.area);
    printf("The perimeter of the rectangle is:%d\n",data.perimeter);
    return 0;
}
