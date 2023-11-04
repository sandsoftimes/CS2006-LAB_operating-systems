// COMMUNICATION BETWEEN DIFFERENT ANCESTRY PROCESSES
#include<unistd.h>
#include<string.h>
#include<fcntl.h> 
#include<stdio.h>
int main(){
    // char str[256] = "" ;
    char str2[256]="";
    char str3[256]="Hello World";
    //open "pipe_one" with READ only mode  and return its file descriptor
    // int fifo_read = open("pipe_one", O_RDONLY) ;
    int fifo_read2=open("pipe_one",O_RDONLY);
    int fifo_write2=open("pipe_two",O_WRONLY);
    //check if open call was successful
    // if (fifo_read < 0){
    //     printf(" Error in opening file \n");
    // }
    if(fifo_read2<0){
        printf("Error in opening file\n");
    }
    // else {
    //     while(strcmp(str, "ImDone") != 0){ 
    //         // Reading text from Opend pipe
    //         read(fifo_read, str, sizeof(str));
    //         // Printing text which is read from the PIPE
    //         printf("** Text: %s \n",str);
    //     }
    //     close(fifo_read);
    // }
    else{
        while(strcmp(str2,"ImDone")!=0){
            read(fifo_read2,str2,sizeof(str2));
            printf("**Text:%s\n",str2);
        }
        close(fifo_read2);
    }
    if(fifo_write2<0){
        printf("Error in opening file\n");
    }
    else{
        while(strcmp(str3,"ImDone")!=0){
            printf("Enter text: \n");
            scanf("%s",&str3);
            write(fifo_write2,str3,sizeof(str3));
            printf("*s%s\n",str3);
        }
        close(fifo_write2);
    }
    return 0;
}