#include<unistd.h>
#include<string.h>
#include<fcntl.h> 
#include<stdio.h>
int main(){ 
    char buffer [20] = "Hello World Boi!!!"; 
    char buffer2 [20];
    // printf("Enter string: \n"); 
    int file = open("file.txt",O_WRONLY);
    write(file, buffer, sizeof(buffer));
    close(file);
    file = open("file.txt",O_RDONLY);
    read(file, buffer2, sizeof(buffer));
    printf("** Text: %s \n",buffer2);
    close(file);
    return 0;
}