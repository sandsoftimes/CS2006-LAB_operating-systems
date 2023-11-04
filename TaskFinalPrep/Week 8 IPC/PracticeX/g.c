#include<unistd.h>
#include<string.h>
#include<fcntl.h> 
#include<stdio.h>
int main(){ 
    char buffer [20] = "Hello World Boi!!!"; 
    char buffer2 [20];
    char buffer3[90]="Yo what's up?";
    char buffer4[90];
    int file2=open("boi.txt",O_WRONLY);

    printf("Enter string: \n"); 
    int file = open("file.txt",O_WRONLY);
    write(file, buffer, sizeof(buffer));
    write(file2,buffer3,sizeof(buffer3));
    close(file);
    close(file2);
    file = open("file.txt",O_RDONLY);
    file2=open("boi.txt",O_RDONLY);
    read(file2,buffer4,sizeof(buffer3));
    read(file, buffer2, sizeof(buffer));
    printf("** Text: %s \n",buffer2);
    printf("** Text: %s \n",buffer4);
    close(file);
    close(file2);
    return 0;
}
