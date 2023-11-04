    // COMMUNICATION BETWEEN DIFFERENT ANCESTRY PROCESSES
#include<unistd.h>
#include<string.h>
#include<fcntl.h> 
#include<stdio.h>
int main(){
    char str2[256]="Hello World";
    char str3[256]="";
    // char str[256] = "hello world";
    // int fifo_write ;
    int fifo_write2;
    fifo_write2=open("pipe_one",O_WRONLY);
    int fifo_read2=open("pipe_two",O_RDONLY);
    if(fifo_write2<0)
        printf("Error opening pipe");
    //open " pipe_one " with WRITE only mode // and return its file descriptor 
    // fifo_write = open("pipe_one",O_WRONLY); 
    // //check if open call was successful
    // if (fifo_write < 0){
    //     printf(" Error opening file \n");
    // }
    // else {
    //     while(strcmp(str, "ImDone") != 0){ 
    //         printf(" Enter text: \n");
    //         scanf("%s",&str);
    //         write (fifo_write , str , sizeof(str));
    //         printf("* %s *\n",str);
    //     }
    //     close(fifo_write);
    // }
    else{
        while(strcmp(str2,"ImDone")!=0){
            printf("Enter text: \n");
            scanf("%s",&str2);
            write(fifo_write2,str2,sizeof(str2));
            printf("*s%s\n",str2);
        }
        close(fifo_write2);
    }
    if(fifo_read2<0){
        printf("Error opening pipe");
    }
    else{
        while(strcmp(str3,"ImDone")!=0){
            read(fifo_read2,str3,sizeof(str3));
            printf("**Text:%s\n",str3);
        }
        close(fifo_read2);
    }
    return 0;
}